#include "timer16B0.h"
#include "motormove.h"
#include "satus.h"




void timer16B0Init(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);				//timer32_0 clock inable
	LPC_TMR16B0->IR |= (1<<0);									// claer intrupt
	LPC_TMR16B0->MCR |= (1<<0) | (1<<2);				// mach 0 intrrupt enable , stop timer when mached
	//LPC_TMR16B0->PR = 1;
	NVIC_EnableIRQ(TIMER_16_0_IRQn);
}

void timer16B0Start(void)
{
	LPC_TMR16B0->TCR |= (1<<0);
}

void timer16B0Stop(void)
{
	LPC_TMR16B0->TCR &= ~(1<<0);
}


void timer16B0Reset(void)
{
	LPC_TMR16B0->TCR |= (1<<1);
	LPC_TMR16B0->TCR &=~(1<<1);
}

void timer16B0SetPrescaler(uint32_t PR)
{
	LPC_TMR16B0->PR = PR;
}

void timer16B0SetMatch(uint32_t match)
{
	LPC_TMR16B0->MR0 = match;
}



void TIMER16_0_IRQHandler(void)
{
	LPC_TMR16B0->IR |= 1<<0;		// claer intrupt
	motorDirection(0);
	
  
}


