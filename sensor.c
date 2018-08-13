#include "sensor.h"
#include "satus.h"


_Bool s1Flag;
 _Bool s2Flag;
 _Bool s3Flag;


void sensorInit()
{
	
LPC_GPIO2->DIR&=~(1<<5);  //S1
LPC_GPIO2->DIR&=~(1<<4);  //S2
LPC_GPIO1->DIR&=~(1<<9);	//S3

}


void getReadSensor()
{
	int Sensor1true=1;
	int Sensor2true=1;
	int Sensor3true=1;
	
	if(panelLEftRightFlag) 
	{
		
    if(LPC_GPIO2->DATA &(1<<5)) //S1	
		{
			for(int i = 0 ;i <= 900000; i++)
			{
				Sensor1true=((LPC_GPIO2->DATA &(1<<5))>>5);
				Sensor1true*=Sensor1true;			
			}
        if(Sensor1true)
					 s1Flag=1;			
			
		 
		}	
		else
			s1Flag=0;
    if(LPC_GPIO2->DATA&(1<<4)) //S2
		  s2Flag=1;
		else 
			s2Flag=0;
   if( LPC_GPIO1->DATA&(1<<9))	//S3
		  s3Flag=1;
		else
			s3Flag=0;
		
	}
  else
	{

    if(LPC_GPIO2->DATA &(1<<5)) //S1
		  s3Flag=1;
		else
			s3Flag=0;
    if(LPC_GPIO2->DATA&(1<<4)) //S2
		  s2Flag=1;
		else 
			s2Flag=0;
   if( LPC_GPIO1->DATA&(1<<9))	//S3
	 
    {

			for(int i = 0 ;i <= 900000; i++)
			{
				Sensor1true=((LPC_GPIO1->DATA &(1<<9))>>9);
				Sensor1true*=Sensor1true;			
			}
        if(Sensor1true)
					 s1Flag=1;

    }
		else
			s1Flag=0;
	
  }		
	
	
	
}


