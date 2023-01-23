#ifndef USART_H
#define USART_H
#include "stm32f10x.h"

void Conf(USART_TypeDef*USARTn);
void Conf_Emission(USART_TypeDef*USARTn);
void Conf_Reception (USART_TypeDef*USARTn);
void envoi_data(USART_TypeDef*USARTn, char data);
char reception_data(USART_TypeDef*USARTn);
void Active_IT(USART_TypeDef * USARTn, char Prio, void(*IT_function)(void));
	
#endif
