#include <stm32f10x.h>
#include <MyTimer.h>


void (*pFnc1)(void);
void (*pFnc2)(void);
void (*pFnc3)(void);
void (*pFnc4)(void);

void TIM1_UP_IRQHandler(void){
	if (pFnc1 != 0){
		(*pFnc1)();
	}
}

void TIM2_IRQHandler(void){
	if (pFnc2 != 0){
		(*pFnc2)();
	}
}

void TIM3_IRQHandler(void){
	if (pFnc3 != 0){
		(*pFnc3)();
	}
}

void TIM4_IRQHandler(void){
	if (pFnc4 != 0){
		(*pFnc4)();
	}
}

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ){
	if(Timer->Timer == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}
	else if (Timer->Timer == TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}
	else if (Timer->Timer == TIM3){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}
	else if(Timer->Timer == TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	Timer->Timer->ARR = Timer->ARR;
	Timer->Timer->PSC = Timer->PSC;
}


void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void(*IT_function)(void)){
	if (Timer == TIM1){
		NVIC_EnableIRQ (TIM1_UP_IRQn);
		NVIC_SetPriority(TIM1_UP_IRQn, Prio);
		pFnc1 =IT_function;
	}else if(Timer==TIM2){
		NVIC_EnableIRQ (TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, Prio);
		pFnc2 =IT_function;
	}else if(Timer==TIM3){
		NVIC_EnableIRQ (TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, Prio);
		pFnc3 =IT_function;
	}else if(Timer==TIM4){
		NVIC_EnableIRQ (TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, Prio);
		pFnc4 =IT_function;
	}
	Timer->DIER |= TIM_DIER_UIE;
}

void MyTimer_PWM(TIM_TypeDef*Timer, char Channel){
	if(Timer == TIM1){
		Timer->BDTR |= TIM_BDTR_MOE;
	}
	if (Channel == 1){
		Timer->CCR1 = 0x5000; //value ? 
		Timer->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);
		Timer->CCMR1 &= ~(TIM_CCMR1_CC1S);
		//Timer->CCMR1 |= TIM_CCMR1_OC1CE;
		Timer->CCER |= TIM_CCER_CC1E;
	}else if(Channel==2){
		Timer->CCR2 = 0x5000;
		Timer->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);
		Timer->CCMR1 &= ~(TIM_CCMR1_CC2S);
		//Timer->CCMR1 |= TIM_CCMR1_OC2CE;
		Timer->CCER |= TIM_CCER_CC2E;
	}else if (Channel ==3){
		Timer->CCR3 = 0x5000;
		Timer->CCMR2 |= (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1);
		Timer->CCMR2 &= ~(TIM_CCMR2_CC3S);
		//Timer->CCMR2 |= TIM_CCMR2_OC3CE;
		Timer->CCER |= TIM_CCER_CC3E;
	}else if(Channel ==4){
		Timer->CCR4 = 0x5000;
		Timer->CCMR2 |= (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1);
		Timer->CCMR2 &= ~(TIM_CCMR2_CC4S);
		//Timer->CCMR2 |= TIM_CCMR2_OC4CE;
		Timer->CCER |= TIM_CCER_CC4E;
	}
}

// Ajout pour faire le bordage

void set_duty_cycle(MyTimer_Struct_TypeDef * Timer, char channel, int pourcentage){
	if (channel == 1) {
		Timer->Timer->CCR1 = Timer->ARR * pourcentage / 100;
	}
	if (channel == 2) {
		Timer->Timer->CCR2 = Timer->ARR * pourcentage / 100;
	}
	if (channel == 3) {
		Timer->Timer->CCR3 = Timer->ARR * pourcentage / 100;
	}
	if (channel == 4) {
		Timer->Timer->CCR4 = Timer->ARR * pourcentage / 100;
	}
}
