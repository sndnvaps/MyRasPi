#ifndef DHT22_H
#define DHT22_H
#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#ifndef  MAXTIMINGS 
#define MAXTIMINGS 85
#endif 

#ifdef DEBUG_
#define DEBUG 1
#else
#define DEBUG 0
#endif
#define DHTPIN 7

void GetDht22_data(float *temp, float * hum);
#endif

