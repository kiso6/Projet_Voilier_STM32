#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"


void MyADC_Start(ADC_TypeDef *ADC);
void ADC1_2_IRQHandler(void);
void MyADC_Active_IT(ADC_TypeDef*ADC,char Prio,void(*IT_function)(void));
void MyADC_SingleNotCont(ADC_TypeDef*ADC,char Channel); //Nécessite des IT
void MyADC_SingleCont(ADC_TypeDef*ADC,char Channel); // Ne nécéssite pas d'it, lecture dans DR à la volée
int MyADC_Read_DR(ADC_TypeDef*ADC);


//void MyADC_ScanNotContDMA(MyADC*ADC);
//void MyADC_ScanContDMA(MyADC*ADC);
//void MyADC_SingleNotContDMA(MyADC*ADC);
//int MyADC_Read_DMA(MyADC*ADC);

#endif
