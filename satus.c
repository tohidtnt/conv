#include "satus.h"


_Bool panelStartFlag;
_Bool panelStopFlag;
_Bool panelLEftRightFlag;
_Bool fromOutStartFlag;
_Bool fromOutStopFlag;

	int panelStartTrue=1;
	int fromOutStartTrue=1;
  unsigned int boardCounter=0;


//---------------PANEL IO SET TO INPUT----------------
void iOInit()
{
	
	
LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); 	
LPC_GPIO0->DIR&=~(1<<3);  //PANEL STOP
LPC_GPIO0->DIR&=~(1<<6);  //PANEL RIGHT
LPC_GPIO2->DIR&=~(1<<1);	//PANEL START
LPC_GPIO2->DIR&=~(1<<9);	//PANEL LEFT	
	
LPC_GPIO1->DIR&=~(1<<1);  // From Out Start
LPC_GPIO1->DIR&=~(1<<2);  //  From Out Stop
	
	
LPC_GPIO0->DIR|=(1<<8);	//  To out status 1
LPC_GPIO0->DIR|=(1<<9);	//	To out status 2

	



}
//------------------------------------------------------

int getReadPanelStartStop()
{
if (LPC_GPIO2->DATA &(1<<1))// (start button press) 2_1
  {
					for(int i = 0 ;i <= 400000; i++)
			{
				panelStartTrue=((LPC_GPIO2->DATA &(1<<1))>>1);
				panelStartTrue*=panelStartTrue;			
			}
        if(panelStartTrue)
	       	panelStartFlag=1;
   
	}
else
	 panelStartFlag=0;
  
if (!(LPC_GPIO0->DATA &(1<<3))) //Stop panel press
   panelStopFlag=1;
else
	 panelStopFlag=0;
return 1;

	
}


int getReadPanelLeftRight()
{
		if( (LPC_GPIO0->DATA &(1<<6)) )  //panel set to right
	     panelLEftRightFlag=1;
		else
			 panelLEftRightFlag=0;
	  if( (LPC_GPIO2->DATA &(1<<9)) )  //panel set to left
   		 panelLEftRightFlag=1;
		else
			 panelLEftRightFlag=0;
	return 1;
	
}
void getReadIoFromOut()
{
  if(  (LPC_GPIO1->DATA & (1<<1))  )  // From Out Start
	{
					for(int i = 0 ;i <= 400000; i++)
			{
				fromOutStartTrue=((LPC_GPIO1->DATA &(1<<1))>>1);
				fromOutStartTrue*=fromOutStartTrue;			
			}
        if(fromOutStartTrue)
		      fromOutStartFlag=1;
	}
  else
		fromOutStartFlag=0;	
	
	
  if(  (LPC_GPIO1->DATA & (1<<2))  )  //  From Out Stop
		fromOutStopFlag=1;
	else 
		fromOutStopFlag=0;
	
}	

 void callPap( unsigned int time)
{
	 
	LPC_GPIO0->DATA |=(1<<9);	//	 Trig PAP with con 13 left pin
	
}

void sayToPapStatus(_Bool busy)
{
	if (busy)
		LPC_GPIO0->DATA |=(1<<9);	//	 say to pap im busy by con 13 right pin
	else
		LPC_GPIO0->DATA &=~(1<<9);	//	Cler Busy 

}



