#include "lpc13xx.h"




#ifndef __satus_h
#define __satus_h


extern _Bool panelStopFlag;
extern _Bool panelStartFlag;
extern _Bool panelLEftRightFlag;
extern _Bool fromOutStartFlag;
extern _Bool fromOutStopFlag;
extern unsigned int boardCounter;

int getReadPanelStartStop();
void	iOInit();
int getReadPanelLeftRight();
void getReadIoFromOut();
void callPap();
void sayToPapStatus(_Bool busy);


#endif
