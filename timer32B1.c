#include "timer32B1.h"
#include "motormove.h"
#include "satus.h"


Timer1CallBack timer1CallBack;

void timer32B1Init(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);				//timer32_0 clock inable
	LPC_TMR32B1->IR |= (1<<0);									// claer intrupt
	LPC_TMR32B1->MCR |= (1<<0) | (1<<2);				// mach 0 intrrupt enable , stop timer when mached
	LPC_TMR32B1->PR = 1;
	NVIC_EnableIRQ(TIMER_32_1_IRQn);
}

void timer32B1Start(void)
{
	LPC_TMR32B1->TCR |= (1<<0);
}

void timer32B1Stop(void)
{
	LPC_TMR32B1->TCR &= ~(1<<0);
}


void timer32B1Reset(void)
{
	LPC_TMR32B1->TCR |= (1<<1);
	LPC_TMR32B1->TCR &=~(1<<1);
}

void timer32B1SetPrescaler(uint32_t PR)
{
	LPC_TMR32B1->PR = PR;
}

void timer32B1SetMatch(uint32_t match)
{
	LPC_TMR32B1->MR0 = match;
}

void timer32B1SetFunctionOnMatch(Timer1CallBack tcb)
{
	timer1CallBack = tcb;
}

void TIMER32_1_IRQHandler(void)
{
	LPC_TMR32B1->IR |= 1<<0;		// claer intrupt
	motorDirection(0);
  
}

void __delay(void)
{
	
	for (int i=0 ; i<= 9999900; i++);

}

