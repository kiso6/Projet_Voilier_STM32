#include "USART.h"
#include "stm32f10x.h"

void (*pFnc1_1)(void);
void (*pFnc2_2)(void);
void (*pFnc3_3)(void);

void USART1_IRQHandler(void){
	if (pFnc1_1 != 0){
		(*pFnc1_1)();
	}
}

void USART2_IRQHandler(void){
	if (pFnc2_2 != 0){
		(*pFnc2_2)();
	}
}

void USART3_IRQHandler(void){
	if (pFnc3_3 != 0){
		(*pFnc3_3)();
	}
}

void Conf(USART_TypeDef*USARTn){
	if (USARTn == USART1){
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		USARTn->BRR = 0x1D4C;
	}else if(USARTn == USART2){
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		USARTn->BRR = (0x0EA6);
	}else if (USARTn == USART3){
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		USARTn->BRR = (0x1D4C);
	}
	USARTn->CR1 |= USART_CR1_UE;
	USARTn->CR1 &= ~USART_CR1_M;
	USARTn->CR2&= ~USART_CR2_STOP;
}

void Conf_Emission(USART_TypeDef*USARTn){
	USARTn->CR1 |= USART_CR1_TCIE;
	USARTn->CR1 |= USART_CR1_TE;

}

void Conf_Reception(USART_TypeDef*USARTn){
	USARTn->CR1 |= USART_CR1_RXNEIE;
	USARTn->CR1 |= USART_CR1_RE;
}

void envoi_data(USART_TypeDef*USARTn, char data){
		USARTn->DR = data;	
		while (((USARTn->SR)&(USART_SR_TXE)) != (USART_SR_TXE)){}
}

char reception_data(USART_TypeDef*USARTn){	
	return USARTn->DR;
}

void Active_IT(USART_TypeDef * USARTn, char Prio, void(*IT_function)(void)){
	if (USARTn == USART1){
		NVIC_EnableIRQ (USART1_IRQn); //n37
		NVIC_SetPriority(USART1_IRQn, Prio);
		pFnc1_1 =IT_function;
	}else if (USARTn == USART2){
		NVIC_EnableIRQ (USART2_IRQn); //n38
		NVIC_SetPriority(USART2_IRQn, Prio);
		pFnc2_2 =IT_function;
	}else if (USARTn == USART3){
		NVIC_EnableIRQ (USART3_IRQn); //n39
		NVIC_SetPriority(USART3_IRQn, Prio);
		pFnc3_3 =IT_function;
	}
}

