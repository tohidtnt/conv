#include "lpc13xx.h"


#ifndef __sensor_h
#define __sensor_h



extern _Bool s1Flag;
extern _Bool s2Flag;
extern _Bool s3Flag;

void sensorInit();
void getReadSensor();




#endif
