#ifndef systickh
#define systickh
#include "stm32f10x.h"

#define SystickTimer 20 //période en ms

void systick_Init(int periode);
void SysTick_Handler (void);
void Systick_ActiveIT (void (*fun) (void));
#endif
