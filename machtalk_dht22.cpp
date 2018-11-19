
//machtalk_upload.cpp 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <mutex>
//#include "config.h"
#ifdef SUPPORT_MYSQL_DB
#include "record_temp.hpp"
#endif 

extern "C" {
#include "dht22.h"
#include "machtalk.h"
#include "rpi_cpu_temp.h"
}

using namespace std;
std::mutex g_mutex;

//#define api_token "95345cb2cbc945da978afb4441da6bcf"

#ifdef SUPPORT_MYSQL_DB
using namespace  RPI_TEMP_RECORD;

std::string float2string(float val) {
	stringstream ss(stringstream::in | stringstream::out);
	ss << val;
	std::string out = ss.str();
	return out;
}
/*
void Insert(string temp,string hum) {
	RPI_TEMP_RECORD::Insert(temp,hum);
	cout<< "inster into table" << endl;
}
*/
void Insert(string temp,string hum,string rpi_cpu_temp) {
	insert(temp,hum,rpi_cpu_temp);
	cout<< "inster into table" << endl;
}

#endif 


void Machtalk_Post(string api_token,string device_id, string device_value_id, string device_value_type_id, float value, int overtime) {
     g_mutex.lock();
     machtalk_post(api_token.c_str(),device_id.c_str(),device_value_id.c_str(),device_value_type_id.c_str(),value,overtime);
     g_mutex.unlock();

}   


int main() {
    float temp;
    float hum;
    float rpi_cpu_temp;
//    string api_token = "95345cb2cbc945da978afb4441da6bcf"; //Replace with you api_token
//    string device_id  = "df104baddce24fd0a5e976c90fc07df3";  //Replace with you device_id 
    GetDht22_data(&temp, &hum);
    rpi_cpu_temp = Get_rpi_temp();
#ifdef SUPPORT_MYSQL_DB
	Insert(float2string(temp),float2string(hum),float2string(rpi_cpu_temp));
#endif 
//     std::thread t1; //t1 is not a thread 
//     std::thread t2(Machtalk_Post,api_token,device_id,"1","1",temp,3);
//     std::thread t3(Machtalk_Post,api_token,device_id,"2","1",hum,3);
//     std::thread t4(Machtalk_Post,api_token,device_id,"3","1",rpi_cpu_temp,3);
//    
//     t2.join();
//     t3.join();   
//     t4.join();
   return 0;
}

