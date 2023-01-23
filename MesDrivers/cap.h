#ifndef CAP_H
#define CAP_H
#include "stm32f10x.h"
#include "Driver_GPIO.h"								
#include "MyTimer.h"										
#include "MyADC.h"											
#include "USART.h"											                
#include "math.h"
#include "MySPI.h"

void init_cap(void);
void Rotation(signed char commande/*, MyTimer_Struct_TypeDef TIMER, MyGPIO_Struct_TypeDef Out*/);

#endif
