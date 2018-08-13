#include <lpc13xx.h>

#ifndef __EXTI_H	
#define __EXTI_H

#define EXTI_PIN_ADDR								(1<<1)

typedef void(*ExtiCallBack)();

typedef enum {FALLING = 0, RISING = 1, EDGE = 2} ExtiIntMode;

extern ExtiCallBack extiCallBack;
void extiInit(LPC_GPIO_TypeDef * gpio, uint8_t pin, ExtiIntMode intMode, ExtiCallBack ecb);
void extiSetFunctionOnReceivedData(ExtiCallBack ecb);

#endif
