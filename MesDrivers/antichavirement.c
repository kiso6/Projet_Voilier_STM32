#include "stm32f10x.h"
#include "antichavirement.h"

MyTimer_Struct_TypeDef Timer_servo;
MyGPIO_Struct_TypeDef  GPIO_servo;
char Z0, Z1, Y0, Y1;
float Z,Y; //short
float aux;
float roulis;

void init_antichav(){
	//Config' Timer-paramètres
  // MyTimer_Struct_TypeDef * Timer_bordage; // à mettre en dehors de la fonction car déclaration
	Timer_servo.Timer = TIM2;
	Timer_servo.ARR = 20000; 
	Timer_servo.PSC = 72; 

  //MyGPIO_Struct_TypeDef * GPIO_bordage; // à mettre en dehors de la fonction car déclaration
	GPIO_servo.GPIO = GPIOA;
	GPIO_servo.GPIO_Pin = 1;
	GPIO_servo.GPIO_Conf = AltOut_Ppull;

	MyGPIO_Init(&GPIO_servo);
	MyTimer_Base_Init(&Timer_servo);
	MyTimer_PWM(Timer_servo.Timer,2);
	Timer_servo.Timer->CR1 |= TIM_CR1_CEN;
}

void ADXL_Init(){
	
	MySPI_Init(SPI2);
	MySPI_Clear_NSS();
	MySPI_Send(W|SB|0x2D);
	MySPI_Send(1<<3);
	MySPI_Set_NSS();
	
	MySPI_Clear_NSS();
	MySPI_Send(W|SB|0x2C);
	MySPI_Send(0x09);
	MySPI_Set_NSS();
	
	MySPI_Clear_NSS();
	MySPI_Send(W|SB|0x31);
	MySPI_Send(0x0B);
	MySPI_Set_NSS();
	
}

float get_roulis(){
	
	
	MySPI_Clear_NSS();
	MySPI_Send(R|MB|0x34);
	Y0=MySPI_Read();
	Y1=MySPI_Read(); 
	Z0=MySPI_Read();
	Z1=MySPI_Read(); 
	MySPI_Set_NSS();
	Z=Z1<<8|Z0;
	Y=Y1<<8|Y0;
	aux=Y/Z;
	return atanf(aux);	
}

void antichavirement(){
	
	roulis=get_roulis();
	if (0.7<roulis){ //on choisit la condition roulis>0.67 car on a vu grâce au Watch que à 0 roulis=0 et à 90° roulis =1.5 on fait ensuite une loi de 3
		set_duty_cycle(&Timer_servo,2,5);
		//roulis=0.0;
	}
}
