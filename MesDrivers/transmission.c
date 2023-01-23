#include "stm32f10x.h"
#include "transmission.h"

MyGPIO_Struct_TypeDef UTX;
MyGPIO_Struct_TypeDef URX;
MyGPIO_Struct_TypeDef AD;


void init_transmission(){

		UTX.GPIO=GPIOA;
    UTX.GPIO_Pin=9;
    UTX.GPIO_Conf = AltOut_OD;
    MyGPIO_Init(&UTX);
	
		URX.GPIO=GPIOA;
    URX.GPIO_Pin=10;
    URX.GPIO_Conf = In_PullUp;
    MyGPIO_Init(&URX);
	
		AD.GPIO=GPIOA;
    AD.GPIO_Pin=5;
    AD.GPIO_Conf = Out_Ppull;
    MyGPIO_Init(&AD);
    MyADC_Start(ADC2);
	
	  Conf(USART1);
    Conf_Emission(USART1);
    Conf_Reception(USART1);

}

void USART_Transmit_String(USART_TypeDef*USARTn,char *str){
	while (*str != '\0')
	envoi_data(USARTn,*str++);
}

void envoi_info(USART_TypeDef*USARTn,char*message){
	USART_Transmit_String(USARTn,message);
}

void lecture_batterie(ADC_TypeDef*ADC,char Channel){
	MyADC_SingleCont(ADC,Channel);
	if (ADC->DR <= 0x43F){
		envoi_info(USART1,"Alert\r\n");
	}
}
