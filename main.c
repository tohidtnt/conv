//MRS-CO Convayer
//Tohid ///AMGMANN
//1397/05/14 19:37


#include "lpc13xx.h"
#include "MotorMove.h"
#include "pwm.h"
#include "adc.h"
#include "satus.h"
#include "sensor.h"
#include "timer16B0.h"
#include "timer32B1.h" //

_Bool startKeyStatus=0 ;
_Bool fromOutStartStats=0;
//unsigned int  boardCounter;


#define pwmPeriod 50 //Period Time set to 1mS

int main()
{
	SystemInit();  //Assuming CCLK (System Clock) = 72Mhz (set by startup code)
	iOInit();	
	pwmInit();
  motorInit();
	adcInit();
	sensorInit();
	
	timer32B1Init();
	timer16B0Init();
	
	

	
	timer32B1SetPrescaler(71999999); // set prescaler evry 1 sec 
	timer16B0SetPrescaler(71999999); // set prescaler evry 10 sec 
	
	timer32B1SetMatch(3);   // matchh evry 3 sec
  timer16B0SetMatch(90000);
	
	_Bool tempSens1HighToLow=1;
	_Bool tempSens1LowToHigh=0;
	
	_Bool tempSens2HighToLow=1;
	_Bool tempSens2LowToHigh=0;
	
	_Bool tempSens3HighToLow=0;
	_Bool tempSens3LowToHigh=0;

	
 __delay(); // simple delay (wait for sensors startup)

  while(1)
	{ 
		timer16B0Start();
		pwmParam(pwmPeriod ,getAdc(),pwmPeriod,getAdc());
    getReadPanelLeftRight(); //Detect sensor number
		getReadSensor();
	  getReadPanelStartStop();
		getReadIoFromOut();
			if(( s2Flag & !tempSens2LowToHigh ) || panelStopFlag || fromOutStopFlag )  // stop sensor 2 from low to high
		{
			timer16B0Stop();
		  timer16B0Reset();
		  timer32B1Stop();
		  timer32B1Reset();
		  motorDirection(0);
		}
		
		else if((s1Flag & !s3Flag) || (s1Flag & s3Flag) || (s1Flag & s3Flag) || fromOutStartFlag || panelStartFlag ) //move
		{ 
			if(s1Flag & !tempSens1LowToHigh) // s1 state low to high check
				 boardCounter++;
			
			if(fromOutStartFlag)
				 callPap();	
			
			move();
			timer16B0Stop();
		  timer16B0Reset();
		  timer32B1Stop();
		  timer32B1Reset();
		}	

		
		if(s3Flag & !tempSens3LowToHigh) //s3 state low to High check
		{
			timer16B0Stop();
		  timer16B0Reset();
			timer32B1Stop();
		  timer32B1Reset();	
		}
		if(!s3Flag & tempSens3HighToLow) //s3 state high to low check
		{
			
			if (boardCounter>0)
         boardCounter--;
			if (boardCounter==0)
			   timer32B1Start();
		}
    if(s3Flag)
		{
			timer16B0Stop();
		  timer16B0Reset();
		}	
		
		  tempSens1LowToHigh=s1Flag;
	    tempSens1HighToLow=s1Flag;
		
		  tempSens2LowToHigh=s2Flag;
	    tempSens2HighToLow=s2Flag;
		
		  tempSens3LowToHigh=s3Flag;
	    tempSens3HighToLow=s3Flag; 
		
		if (boardCounter!=0)
			sayToPapStatus(1); //busy
		else
			sayToPapStatus(0); //clear busy
			
		
	
   }
	

	

}
//    s3 s2 s1
//    0  0  0 ->  0  null
//    0  0  1 ->  1  move ok
//    0  1  0 ->  2  stop
//    0  1  1 ->  3  STOP ok
//    1  0  0 ->  4  timer
//    1  0  1 ->  5  move ok
//    1  1  0 ->  6  STOP
//    1  1  1 ->  7  STOP ok






