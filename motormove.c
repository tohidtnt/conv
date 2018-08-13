#include "MotorMove.h"
#include "satus.h"
#include "adc.h"
#include "pwm.h"

#define pwmPeriod 50 //Period Time set to 1mS

int motorStatusFlag;

void motorInit()
	{
		
		
//  LPC_GPIO1->DIR|=(1<<6)|(1<<7);
//  LPC_GPIO1->DATA=(1<<6)|(1<<7);
		LPC_IOCON->PIO1_6|=(1<<4);
 //--------------motor pin direction to  output------		
   LPC_GPIO2->DIR|=(1<<0)|(1<<3); 
   LPC_GPIO3->DIR|=(1<<1)|(1<<3);	
//-------------------------------------------------
		
	}

int motorDirection(  int Direction)
{



  if(Direction==1)	
   {	
		motorStatusFlag=1;
    LPC_GPIO2->DATA|=(1<<0);  // 
    LPC_GPIO3->DATA&=~(1<<3); 
		LPC_GPIO2->DATA&=~(1<<3);
    LPC_GPIO3->DATA|=(1<<1); 

   }	
	if(Direction==2)
	{ 
		motorStatusFlag=2;
    LPC_GPIO2->DATA&=~(1<<0);  // 
    LPC_GPIO3->DATA|=(1<<3); 
		LPC_GPIO2->DATA|=(1<<3);
    LPC_GPIO3->DATA&=~(1<<1); 
  }		
	if (Direction==0)
	{	
		motorStatusFlag=0;
    LPC_GPIO2->DATA&=~(1<<0);  // stop
    LPC_GPIO3->DATA&=~(1<<3); 	
    LPC_GPIO2->DATA&=~(1<<3);
    LPC_GPIO3->DATA&=~(1<<1); 		
	}	
	return 1;
}	




 void move()
{
	if(panelLEftRightFlag)
	{
		motorDirection(2); 
	}
	else
	{
		motorDirection(1);
	}
		
}


		
	
	  
		
		  
	
	
	

