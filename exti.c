#include "exti.h"

ExtiCallBack exti0CallBack[16];
ExtiCallBack exti1CallBack[16];
ExtiCallBack exti2CallBack[16];
ExtiCallBack exti3CallBack[16];

void extiInit(LPC_GPIO_TypeDef * gpio, uint8_t pin, ExtiIntMode intMode, ExtiCallBack ecb)
{	
	gpio->IE |= 1<<pin;
		if (intMode == RISING)
	gpio->IEV |= 1<<pin;
		else if (intMode == EDGE)
	gpio->IBE |= 1<<pin;		
	 
	
	if(gpio == LPC_GPIO0)
	{
		exti0CallBack[pin] = ecb;
		NVIC_EnableIRQ(EINT0_IRQn);
	}
	else if(gpio == LPC_GPIO1)
	{
		exti1CallBack[pin] = ecb;
		NVIC_EnableIRQ(EINT1_IRQn);
	}
	else if(gpio == LPC_GPIO2)
	{
		exti2CallBack[pin] = ecb;
		NVIC_EnableIRQ(EINT2_IRQn);
	}
	else if(gpio == LPC_GPIO3)
	{
		exti3CallBack[pin] = ecb;
		NVIC_EnableIRQ(EINT3_IRQn);
	}
}

void PIOINT0_IRQHandler(void)
{
	uint8_t i;
	
	for(i = 0; i < 16; i++)
	{
		if(LPC_GPIO0->MIS & (1<<i)) {
			exti0CallBack[i]();
			LPC_GPIO0->IC = 1<<i;
		}
	}
}

void PIOINT1_IRQHandler(void)
{
	uint8_t i;
	
	for(i = 0; i < 16; i++)
	{
		if(LPC_GPIO1->MIS & (1<<i)) {
			exti1CallBack[i]();
			LPC_GPIO1->IC = 1<<i;
		}
	}
}
void PIOINT2_IRQHandler(void)
{
	uint8_t i;
	
	for(i = 0; i < 16; i++)
	{
		if(LPC_GPIO2->MIS & (1<<i)) {
			exti2CallBack[i]();
			LPC_GPIO2->IC = 1<<i;
		}
	}
}

void PIOINT3_IRQHandler(void)
{
	uint8_t i;
	
	for(i = 0; i < 16; i++)
	{
		if(LPC_GPIO3->MIS & (1<<i)) {
			exti3CallBack[i]();
			LPC_GPIO3->IC = 1<<i;
		}
	}
}
