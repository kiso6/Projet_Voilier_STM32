#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H
#include "stm32f10x.h"
	
typedef struct MyGPIO_Struct_TypeDef
{
GPIO_TypeDef * GPIO ;
char GPIO_Pin ; // numero de 0 a 15
char GPIO_Conf ; // voir cidessous
} MyGPIO_Struct_TypeDef ;


#define In_Floating 0x4  
#define In_PullDown 0x8 // pour différencier pull-down et pull-down parec qu'ils ont le même code
#define In_PullUp 16 //on met 16 parce il n'y a aucun autre code qui ont cette valeur
#define In_Analog 0x0
#define Out_Ppull 0x1 
#define Out_OD 0x6
#define AltOut_Ppull 0xB
#define AltOut_OD 0xF 


//garder cette partie pour le .c

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOSructPtr ) ;
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ; // r e n v o i e 0 ou a u t r e chose d i f f e r e n t de 0
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;

#endif
