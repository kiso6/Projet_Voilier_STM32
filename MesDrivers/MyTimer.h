#ifndef MYTIMER_H
#define MYTIMER_H
#include <stm32f10x.h>

typedef struct
{
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} MyTimer_Struct_TypeDef ;
/*
*****************************************************************************************
* @brief
* @param -> Paramètre sous forme d’une structure(son adresse) contenantles
informations de base
* @Note -> Fonction à lancer systématiquement avant d ’ aller plus en détail dans les
conf plus fines (PWM, codeur inc ... )
*************************************************************************************************
*/

void TIM1_UP_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void MyTimer_Base_Init( MyTimer_Struct_TypeDef * Timer ) ;
void MyTimer_ActiveIT( TIM_TypeDef * Timer , char Prio, void (*IT_function)(void) ) ;
void MyTimer_PWM(TIM_TypeDef*Timer, char Channel);
void set_duty_cycle(MyTimer_Struct_TypeDef * Timer, char channel, int pourcentage);

#define MyTimer_Base_Start ( Timer ) ( Timer->CR1 |= TIM_CR1_CEN; )
#define MyTimer_Base_Stop ( Timer ) ( Timer->CR1 &= ~(TIM_CR1_CEN); )

#endif
