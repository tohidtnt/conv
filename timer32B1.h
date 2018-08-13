#include <lpc13xx.h>

#ifndef __timer32B1
#define __timer32B1

typedef void (*Timer1CallBack)();

extern Timer1CallBack timer1CallBack;

void timer32B1Init(void);
void timer32B1Start(void);
void timer32B1Stop(void);
void timer32B1Reset(void);
void timer32B1SetPrescaler(uint32_t PR);
void timer32B1SetMatch(uint32_t match);
void timer32B1SetFunctionOnMatch(Timer1CallBack tcb);
void __delay(void);

#endif
