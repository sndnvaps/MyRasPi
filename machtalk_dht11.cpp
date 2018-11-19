
//machtalk_dht11.cpp 

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
//for std::mutex 
#include <mutex>
//for dht11

extern "C" {

#include "dht11.h"
#include "machtalk.h"

}


using namespace std;

//void GetDht11_data(int *temp, int *rh);

std::mutex g_mutex;


void Machtalk_Post(string api_token,string device_id, string device_value_id, string device_value_type_id, float value, int overtime) {
     g_mutex.lock();
     machtalk_post(api_token.c_str(),device_id.c_str(),device_value_id.c_str(),device_value_type_id.c_str(),value,overtime);
     g_mutex.unlock();

}   





int main() {
   

    int temp = 0;
    int rh      = 0;
//    string api_token = "You machtalk APIToken";
    GetDht11_data(&temp,&rh);
    std::cout << "Temp = " << temp << std::endl; 
    std::cout << "Hum = " << rh << std::endl;
//     std::thread t1; //t1 is not a thread 
//     std::thread t2(Machtalk_Post,api_token,"df104baddce24fd0a5e976c90fc07df3","1","1",temp,3);
//     sleep(10);
//     std::thread t3(Machtalk_Post,api_token,"df104baddce24fd0a5e976c90fc07df3","2","1",rh,3);

//     t2.join();
//     t3.join();
   return 0;
}

