#include "pwm.h"

#define pwmPeriod 50 //Period Time set to 1mS


void pwmInit( int pwmPeriod1  ,int TOnTime1,int pwmPeriod2  ,int TOnTime2)
	
{ 
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9)|(1<<16);      //Enable 32Bit-TMR0 Clock , Enable IOCON
	LPC_IOCON->PIO1_6 &= ~(7<<0);
	LPC_IOCON->PIO1_6 |=2<<0;
	LPC_IOCON->PIO1_7 &= ~(7<<0);
	LPC_IOCON->PIO1_7 |=2<<0;
	LPC_TMR32B0->CTCR = 0x0;
	LPC_TMR32B0->PR = 71;                     //Increment TC at every 71+1 clock cycles 72 clock cycles @72Mhz = 1 us
	LPC_TMR32B0->MCR = (1<<10)|(1<<7);        //Reset on MR3 Match,Reset on MR2 Match
  LPC_TMR32B0->PWMC=0x3;	                  //enable pwm
	LPC_TMR32B0->TCR = 0x2;                   //Reset Timer
}


void pwmParam(int pwmPeriod1  ,int TOnTime1,int pwmPeriod2  ,int TOnTime2)
{
	LPC_TMR32B0->MR3 = pwmPeriod1;                 // Period duration
	LPC_TMR32B0->MR0 = pwmPeriod1-TOnTime1;        // TOFF time in mS
	LPC_TMR32B0->MR2 = pwmPeriod2;                // Period duration
	LPC_TMR32B0->MR1 = pwmPeriod2-TOnTime2;        // TOFF time in mS
	LPC_TMR32B0->TCR = 0x1;                      //Enable timer
}
	






