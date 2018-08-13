#include <lpc13xx.h>

#ifndef __SLEEP
#define __SLEEP

extern _Bool isSleepTimerInited;
extern _Bool isTimeElapsed;

void sleep500us(int time);
void sleepTimerCallBack(void);

#endif
