#include "Driver_GPIO.h"												// GPIO   header
#include "MyTimer.h"										// Timer  header
#include "MyADC.h"											// ADC    header
#include "USART.h"
#include "MySPI.h"
#include "stm32f10x.h"                  // Device header
#include "bordage.h"
#include "transmission.h"	
#include "antichavirement.h"
#include "cap.h"
#include "systick.h"

//variables utilis�es dans le programme
int dec;
char envoi;
extern int compteursystick;

//d�claration systick interrupt
void systick_IT(void);

int main(){
	//On active les clk des GPIO
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
	//Init des GPIO associ�s aux fonctions
	init_girouette();
	init_bordage();
	init_transmission();
	init_cap();
	init_antichav();
	ADXL_Init();
	Systick_ActiveIT(systick_IT);
	systick_Init(20);
	MyADC_Start(ADC2);
	
	while(1){
		//tout est g�r� en systick
	}
}



//Corps de l'interruption systick ex�cut�e dans le handler
void systick_IT(void){
	if (compteursystick % 5 ==0){
		dec=decodeur();
		envoi=reception_data(USART1);
		bordage_voiles(dec);
		Rotation(envoi);
		antichavirement();
	}
	if (compteursystick % 150 ==0){
		//lecture_batterie(ADC2,5); // probl�me sur la fonctionnalit�, d�tection ADC probl�matique
		envoi_info(USART1,"Le voilier navigue\r\n"); // probl�me d'envoi
	}
	
	compteursystick++;

}
