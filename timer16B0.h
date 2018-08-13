#include <lpc13xx.h>

#ifndef __timer16B0
#define __timer16B0



void timer16B0Init(void);
void timer16B0Start(void);
void timer16B0Stop(void);
void timer16B0Reset(void);
void timer16B0SetPrescaler(uint32_t PR);
void timer16B0SetMatch(uint32_t match);



#endif