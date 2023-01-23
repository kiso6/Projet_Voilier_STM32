#include "stm32f10x.h"
#include "MyADC.h"

void(*pFunc1)(void);

void MyADC_Start(ADC_TypeDef *ADC){
	if (ADC == ADC1){
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	}else{
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	}
	ADC->CR2 |= ADC_CR2_ADON;
	ADC->CR2 |= ADC_CR2_CAL;
	ADC->CR2 |= ADC_CR2_SWSTART;
}

void ADC1_2_IRQHandler(void){
	if (pFunc1 != 0){
		(*pFunc1)();
	}
}

void MyADC_Active_IT(ADC_TypeDef*ADC, char Prio, void(*IT_function)(void)){
	ADC->CR1 |= ADC_CR1_EOCIE;
	NVIC_EnableIRQ (ADC1_2_IRQn); //n=18
	NVIC_SetPriority(ADC1_2_IRQn, Prio); //n=18
	pFunc1 = IT_function;
}

void MyADC_SingleNotCont(ADC_TypeDef*ADC,char Channel){
	ADC->CR2 &= ~(1<<ADC_CR2_CONT);
	//ADC->SQR1 |= ADC_SQR1_L_0;
	ADC->SQR3 |= Channel;
}


void MyADC_SingleCont(ADC_TypeDef*ADC,char Channel){
	ADC->CR2 |= ADC_CR2_CONT;
	//ADC->SQR1 |= ADC_SQR1_L_0;
	ADC->SQR3 |= Channel;
}

int MyADC_Read_DR(ADC_TypeDef*ADC){
	return ADC->DR;
}
