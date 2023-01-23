#include "stm32f10x.h"
#include "Driver_GPIO.h"

char Config;

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) {
	
	RCC->APB2ENR |=  (0x01 << 4)|(0x01 << 2) | (0x01 << 3) ; 
	
	Config = GPIOStructPtr->GPIO_Conf;
	
	//On vérifie quel registre de contrôle il faut utiliser 
	if (GPIOStructPtr->GPIO_Pin <8){ //Pin 1 à 7 CRL
		//on met tous les bits à 0 pour ne plus avoir de pb ensuite avec les OU
		GPIOStructPtr->GPIO->CRL = GPIOStructPtr->GPIO->CRL &~ (0xF<<(GPIOStructPtr->GPIO_Pin*4));
		//On vérifie la configuration du GPIO
		if (Config ==16) {
		//On met le regsitre CRL à 0b1000 et pour le différencier de In_PullUp on met le ODR à 1 
		GPIOStructPtr->GPIO->CRL |= (8<<(GPIOStructPtr->GPIO_Pin*4)); //on fait *4 car chaque pin prend 4 bits du registre CRL
		GPIOStructPtr->GPIO->BSRR = (1<<GPIOStructPtr->GPIO_Pin); //on utilise le registre BSRR pour mettre le bit à 1
		} else {
		//On met le regsitre CRL à la valeur de Config
		GPIOStructPtr->GPIO->CRL |= (Config<<(GPIOStructPtr->GPIO_Pin*4));
		}

	}
	else { //Pin 8 à 15 CRH
		//on met tous les bits à 0 pour ne plus avoir de pb ensuite avec les OU
		GPIOStructPtr->GPIO->CRH = GPIOStructPtr->GPIO->CRH &~ (0xF<<(GPIOStructPtr->GPIO_Pin*4-32));
		//On vérifie la configuration du GPIO
		if (Config ==16) {
		//On met le regsitre CRL à 0b1000 et pour le différencier de In_PullUp on met le ODR à 1 
		GPIOStructPtr->GPIO->CRH |= (8<<(GPIOStructPtr->GPIO_Pin*4-32)); //on fait -32 car le registre CRH part du pin 8 soit 32 bits
		GPIOStructPtr->GPIO->BSRR = (1<<GPIOStructPtr->GPIO_Pin); //on utilise le registre BSRR pour mettre le bit à 1
		} else {
		//On met le regsitre CRL à la valeur de Config
		GPIOStructPtr->GPIO->CRH |= (Config<<(GPIOStructPtr->GPIO_Pin*4-32));
		}
		
	}
}


int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	return GPIO->IDR & (1<<GPIO_Pin); //masque et pour trouver la valeur du pin voulu
}

void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
 GPIO->BSRR = (1<<GPIO_Pin); // on utilise le registre BSRR pour set le bit voulu
}

void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	//GPIO->BSRR = (1<<(GPIO_Pin+15));
	GPIO->BRR = (1<<GPIO_Pin); // on utilise le registre BRR pour reset le bit voulu
}

void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	GPIO->ODR ^= (1<<GPIO_Pin);
}


