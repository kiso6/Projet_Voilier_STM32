#ifndef ANTICHAVIREMENT_H
#define ANTICHAVIREMENT_H
#include "stm32f10x.h"
#include "Driver_GPIO.h"								
#include "MyTimer.h"										
#include "MyADC.h"											
#include "USART.h"											                
#include "math.h"
#include "MySPI.h"


#define W 0<<7
#define SB 0<<6
#define R 1<<7
#define MB 1<<6

void init_antichav(void);
void ADXL_Init(void);
float get_roulis(void);
void antichavirement(void);

#endif
