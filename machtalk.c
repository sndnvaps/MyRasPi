/* 
* machtalk.c 
*/


#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h>  
#include <errno.h>  
#include <math.h>
#include <sys/socket.h>  
#include <linux/in.h> 
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>
#include <sys/stat.h>  
#include <fcntl.h> 
#include <unistd.h> 
#include <wiringPi.h>

#include "machtalk.h" 

int  get_cpu_temperature(double *temperature) {
        #define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp" 
        #define MAX_SIZE 32  
    int fd;  
    char buf[MAX_SIZE];  
       
    // 打开/sys/class/thermal/thermal_zone0/temp  
    fd = open(TEMP_PATH, O_RDONLY);  
    if (fd < 0) {  
        fprintf(stderr, "failed to open thermal_zone0/temp\n");  
        return -1;  
    }  
       
    // 读取内容  
    if (read(fd, buf, MAX_SIZE) < 0) {  
        fprintf(stderr, "failed to read temp\n");  
        return -1;  
    }  
       
    // 转换为浮点数打印  
    *temperature = atoi(buf) / 1000.0;  
       
    // 关闭文件  
    close(fd); 
        return 0;
}



void  machtalk_post(const char *api_token,const char *device_id,const char *device_value_id,const char *device_value_type_id,float value,int overtime) {

        int ret;
        int cfd; /* 文件描述符 */
        char* presult;
        char remote_server[] = "dev.api.machtalk.net:12086";
        char str_tmp[128] = {0};
        struct sockaddr_in s_add;
        // 请求缓冲区和响应缓冲区
        static char http_request[1024] = {0};        //声明为静态变量，防止堆栈溢出
        static char http_response[1024] = {0};        //声明为静态变量，防止堆栈溢出
        // Http内容，表单内容
        char http_content[32] = {0};
        struct timeval timeo={3,0};
    socklen_t len = sizeof(struct timeval);
     
        sprintf(str_tmp,"/v1.0/device/%s/%s/%s/datapoints/add",device_id,device_value_id,device_value_type_id);
        // 确定HTTP表单提交内容 params={"value":20}
        sprintf( http_content , "params={\"value\":%.2f}" , value);

        printf("D:%s\n",http_content);
        // 确定 HTTP请求首部
        // 例如POST /v1.0/device/98d19569e0474e9abf6f075b8b5876b9/1/1/datapoints/add HTTP/1.1\r\n
        sprintf( http_request , "POST %s HTTP/1.1\r\n",str_tmp);
        // 增加属性 例如 Host: api.machtalk.net\r\n
        sprintf( str_tmp , "Host:%s\r\n" , remote_server);
        strcat( http_request , str_tmp);
        // 增加密码 例如 APIKey: ffa3826972d6cc7ba5b17e104ec59fa3
        sprintf( str_tmp , "APIKey:%s\r\n" , api_token); 
        strcat( http_request , str_tmp);
        //
        strcat( http_request , "Accept: */*\r\n");
        // 增加提交表单内容的长度 例如 Content-Length:12\r\n
        sprintf( str_tmp , "Content-Length:%d\r\n" ,strlen(http_content) );
        strcat( http_request , str_tmp);
        // 增加表单编码格式 Content-Type:application/x-www-form-urlencoded\r\n
        strcat( http_request , "Content-Type: application/x-www-form-urlencoded\r\n");
        strcat( http_request , "Connection: close\r\n");
        // HTTP首部和HTTP内容 分隔部分
        strcat( http_request , "\r\n");
        // HTTP负载内容
        strcat( http_request , http_content);
         
        /* 构造服务器端的ip和端口信息，具体结构体可以查资料 */  
        bzero(&s_add,sizeof(struct sockaddr_in));  
        s_add.sin_family=AF_INET;  
        s_add.sin_addr.s_addr= inet_addr("60.211.201.42"); /* ip转换为4字节整形，使用时需要根据服务端ip进行更改 */ 
        s_add.sin_port=htons(12086);
 
        /* 建立socket 使用因特网，TCP流传输 */ 
        cfd = socket(AF_INET, SOCK_STREAM, 0);  
        if(-1 == cfd){  
                printf("socket fail ! \r\n");  
                exit(-1);  
        }  
        printf("socket ok !\r\n"); 
        timeo.tv_sec = overtime;
        timeo.tv_usec = 0;
        if (setsockopt(cfd, SOL_SOCKET, SO_SNDTIMEO, &timeo, len) == -1){
                printf("set over time fail ! \r\n");  
                exit(-1); 
        }
        /* 客户端连接服务器，参数依次为socket文件描述符，地址信息，地址结构大小 */ 
        if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))  
        {  
                printf("connect fail !\r\n");  
                exit(-1);  
        }  
        printf("connect ok !\r\n");  
        timeo.tv_sec = overtime;
        timeo.tv_usec = 0;
        if (setsockopt(cfd, SOL_SOCKET, SO_RCVTIMEO, &timeo, len) == -1){
                printf("set over time fail ! \r\n");  
                exit(-1); 
        }
        /*连接成功,发送数据到服务器*/ 
        if(-1 == (ret = send(cfd,http_request,strlen(http_request),MSG_NOSIGNAL)))  
        {  
                close(cfd);
                printf("send data fail !\r\n");  
                exit(-1);  
        } 
        printf("send ok !\r\n"); 
        // 获得响应
        ret = recv(cfd,(unsigned char *)http_response,sizeof(http_response),0);
        if(ret <= 0){
                close(cfd);
                printf("read data fail !\r\n"); 
                 exit(-1);
        }
        printf("recv ok !\r\n"); 
        http_response[ret] = '\0';
        //判断是否收到HTTP OK
        presult = strstr( (const char *)http_response , (const char *)"200 OK\r\n");
        if( presult != NULL ){
                //printf("Http Response OK\r\n");
                presult = strstr( (const char *)http_response , (const char *)"\"success\":1");
                if( presult != NULL ){
                        //printf("POST OK\r\n");
                }else{
                        printf("POST FAILD\r\n");
                }
        }else{
                printf("Http Response Error\r\n");
        }
        close(cfd);
       // exit(0);
}

