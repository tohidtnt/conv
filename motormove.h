#include "lpc13xx.h"


#ifndef __motorMove_h
#define __motorMove_h

extern int motorStatusFlag ;

int motorDirection(int Direction);
void motorInit();
void move();



#endif
