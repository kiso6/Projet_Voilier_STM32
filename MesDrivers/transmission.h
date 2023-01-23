#ifndef TRANSMISSION_H
#define TRANSMISSION_H
#include "stm32f10x.h"
#include "Driver_GPIO.h"								
#include "MyTimer.h"										
#include "MyADC.h"											
#include "USART.h"											                 
#include "MySPI.h"

void init_transmission(void);
void lecture_batterie(ADC_TypeDef*ADC,char Channel);
void envoi_info(USART_TypeDef*USARTn,char*message);
void USART_Transmit_String(USART_TypeDef*USARTn,char *str);


#endif

