#include "stm32f10x.h"
#include "antichavirement.h"
#include "USART.h"
#include "cap.h"

int compteursystick = 0;
void (* handler_systick_ptr) (void);

void systick_Init(int periode){
	SysTick->CTRL |= SysTick_CTRL_ENABLE;
	SysTick->CTRL |= SysTick_CTRL_TICKINT;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;
	SysTick->LOAD |=  (72000000/(1000/periode) - 1);
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 3);
}
void Systick_ActiveIT(void (*IT_function) (void)){
	handler_systick_ptr = IT_function;
}

void SysTick_Handler (void){
	handler_systick_ptr();
}
