#include "sleep.h"
#include "timer32B1.h"

_Bool isSleepTimerInited = 0;
_Bool isTimeElapsed = 0;

void sleep500us(int time)
{
	if(!isSleepTimerInited)
	{
		timer32B1Init();
		timer32B1SetFunctionOnMatch(sleepTimerCallBack);
		timer32B1SetPrescaler(100);
		isSleepTimerInited = 1;
	}
	
	isTimeElapsed = 0;
	timer32B1SetMatch(360 * time);
	timer32B1Start();
	while(!isTimeElapsed);
}

void sleepTimerCallBack()
{
	timer32B1Reset();
	isTimeElapsed = 1;
}
