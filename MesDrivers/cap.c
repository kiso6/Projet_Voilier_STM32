#include "stm32f10x.h"
#include "cap.h"

//Declaration de la sortie de PWM
MyGPIO_Struct_TypeDef Out;
MyGPIO_Struct_TypeDef OutPWM;
MyTimer_Struct_TypeDef TIMER;


void init_cap(){
	Out.GPIO=GPIOA;
	Out.GPIO_Pin=7;
	Out.GPIO_Conf = Out_Ppull;
	MyGPIO_Init(&Out);
	
	OutPWM.GPIO=GPIOA;
	OutPWM.GPIO_Pin=6;
	OutPWM.GPIO_Conf = AltOut_Ppull;
	MyGPIO_Init(&OutPWM);
	
	TIMER.Timer = TIM3;
	TIMER.ARR =100;
	TIMER.PSC=36;
	MyTimer_Base_Init(&TIMER);
	MyTimer_PWM(TIMER.Timer,0x1);
	TIM3->CR1 |= TIM_CR1_CEN;
}


void Rotation(signed char commande/*, MyTimer_Struct_TypeDef TIMER,MyGPIO_Struct_TypeDef Out*/){
	if (commande<0){
		MyGPIO_Reset (Out.GPIO ,Out.GPIO_Pin);
	}else{	
		MyGPIO_Set (Out.GPIO,Out.GPIO_Pin);
	}
	set_duty_cycle(&TIMER, 0x1, commande);
}

