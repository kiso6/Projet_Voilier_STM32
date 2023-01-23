#include "bordage.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include <stm32f10x.h>

#define Angle_index 5  //angle de départ

//Déclaration des Timers et des GPIO pour le bordage des voiles
	MyTimer_Struct_TypeDef Timer_bordage;
	MyGPIO_Struct_TypeDef  GPIO_bordage;
	
//Déclaration des Timers et des GPIO pour la girouette
	TIM_TypeDef * Timer_girouette;
  MyGPIO_Struct_TypeDef  GPIO_girouette_A; //Channel 1
	MyGPIO_Struct_TypeDef  GPIO_girouette_B; //Channel 2
	MyGPIO_Struct_TypeDef  GPIO_girouette_index; //Channel 3 


/////////////////////////////////////////////////////////////////////////////////
///////////////////// Fonction pour initialiser le bordage //////////////////////
/////////////////////////////////////////////////////////////////////////////////

void init_bordage(){
	//Config' Timer-paramètres
  // MyTimer_Struct_TypeDef * Timer_bordage; // à mettre en dehors de la fonction car déclaration
	Timer_bordage.Timer = TIM2;
	Timer_bordage.ARR = 20000; 
	Timer_bordage.PSC = 72; 

  //MyGPIO_Struct_TypeDef * GPIO_bordage; // à mettre en dehors de la fonction car déclaration
	GPIO_bordage.GPIO = GPIOA;
	GPIO_bordage.GPIO_Pin = 1;
	GPIO_bordage.GPIO_Conf = AltOut_Ppull;

	MyGPIO_Init(&GPIO_bordage);
	MyTimer_Base_Init(&Timer_bordage);
	MyTimer_PWM(Timer_bordage.Timer,2);
	Timer_bordage.Timer->CR1 |= TIM_CR1_CEN;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////Fonction pour initialiser la girouette /////////////////////
/////////////////////////////////////////////////////////////////////////////////

void init_girouette(){ //configuration TIM1 en mode incrémental + 3 GPIO pour recevoir les fils de la girouette 
	
	RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_IOPAEN ;// activation clock GPIOA
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN  ;// activation clock TIM1
	
	//Configuration des GPIO de réception de la girouette
	// MyGPIO_Struct_TypeDef * GPIO_girouette_A; //Channel 1 // à mettre en dehors de la fonction car déclaration
	GPIO_girouette_A.GPIO = GPIOB;
	GPIO_girouette_A.GPIO_Pin = 6;
	GPIO_girouette_A.GPIO_Conf = In_Floating;
	
	// MyGPIO_Struct_TypeDef * GPIO_girouette_B; //Channel 2 à mettre en dehors de la fonction car déclaration
	GPIO_girouette_B.GPIO = GPIOB;
	GPIO_girouette_B.GPIO_Pin = 7;
	GPIO_girouette_B.GPIO_Conf = In_Floating;
	
	//MyGPIO_Struct_TypeDef * GPIO_girouette_index; //Channel 3  à mettre en dehors de la fonction car déclaration
	GPIO_girouette_index.GPIO = GPIOB;
	GPIO_girouette_index.GPIO_Pin = 8;
	GPIO_girouette_index.GPIO_Conf = In_Floating;

	MyGPIO_Init(&GPIO_girouette_A);
	MyGPIO_Init(&GPIO_girouette_B);
	MyGPIO_Init(&GPIO_girouette_index);

	//configuration TIM4 en mode incrémental
	//TI1FP1 mapped on TIM4
	Timer_girouette = TIM4;
	Timer_girouette->ARR = 360*4;
	Timer_girouette->CCMR1 &=~ TIM_CCMR1_CC1S_1 ;
	Timer_girouette->CCMR1 |= TIM_CCMR1_CC1S_0 ;
	//TI2FP2 mapped on TIM2
	Timer_girouette->CCMR1 &=~ TIM_CCMR1_CC2S_1 ;
	Timer_girouette->CCMR1 |= TIM_CCMR1_CC2S_0 ;
	// Both inputs are active on both rising and falling edges
	Timer_girouette->SMCR |= TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0 ;
	Timer_girouette->SMCR &=~ TIM_SMCR_SMS_2 ;
	
	Timer_girouette->CR1 |= TIM_CR1_CEN;

}


/////////////////////////////////////////////////////////////////////////////////
///////////// Fonction pour trouver l'angle du bordage des voiles ///////////////
/////////////////////////////////////////////////////////////////////////////////

int decodeur (){
	//Nombre de pulsations comptées par la girouette => Pas un vrai angle
	int angle_girouette;
	int angle_voiles;	
	angle_girouette = (TIM4->CNT+Angle_index*4);
	//Angle que doit prendre la voile en fonction de celui de la girouette
	if (angle_girouette > 0 && angle_girouette < 180){
		angle_voiles = 0;
	}else{
		angle_voiles = (90*angle_girouette/135-30);
	}
	return angle_voiles; //l'angle retourné = angle réel*4
}
/*
//à revoir avec le sauveur
void bordage_voiles(int angle_voiles){
	if ((angle_voiles>0) && (angle_voiles<90)) {
		//set_duty_cycle(&Timer_bordage, 2, (5+(angle_voiles/36)));
		set_duty_cycle(&Timer_bordage, 2, 10);
	}
	else if (angle_voiles=720) set_duty_cycle(&Timer_bordage, 2, 5);
	else {
		set_duty_cycle(&Timer_bordage, 2, (10-((angle_voiles-180)/36)));
	}
}
/////////////////////////////////////////////////////////////////////////////////
*/



void bordage_voiles(int angle_voiles){
	if (((angle_voiles>0) && (angle_voiles<180))|(angle_voiles>1260)) {
		set_duty_cycle(&Timer_bordage, 2, 10);
	} 
	else if (angle_voiles==720) {
		set_duty_cycle(&Timer_bordage, 2, 5);
		}
	else if (angle_voiles>180 && angle_voiles<720){
		set_duty_cycle(&Timer_bordage, 2, (10+(900/540)-5*(angle_voiles/540)));
		}
	else if (angle_voiles>720 && angle_voiles<1260) {
		set_duty_cycle(&Timer_bordage, 2, (-(5/3)+((angle_voiles)/108)));
		}
}


/*
int main(void){
while(1);
}
*/
