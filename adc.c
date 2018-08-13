#include "adc.h"



void adcInit(void)
	

{
	
	
	LPC_SYSCON->PDRUNCFG &= (~(1<<4)) ; //Power-up ADC Block
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13)|(1<<16); //Enable ADC clock
	LPC_ADC->CR = 0x00000F02; //Setup ADC Block
	LPC_IOCON->R_PIO1_0 = 0x2;   //Select PIO1_0 to ADC1
	
	
}
int getAdc(void)
{

	int sum=0;
	unsigned int result = 0;
	LPC_ADC->CR |= (1<<24);  //Start ADC NOW!
	while((LPC_ADC->DR[1] & (1<<31)) == 0); //Wait until conversion is finished
	int x=0;
	for( x=0;x<20;x++)
	{
	result=(LPC_ADC->DR[1]>>6) & 0x3FF; //10 bit Mask to extract result
	sum+=result;		
	}
	result=sum/x;
	//if(result>0x3BA)
		//result=0x3BA;
	
	return result/21;
}
