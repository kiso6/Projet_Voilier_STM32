#include <MyTimer.h>
#include "Driver_GPIO.h"
#include <stm32f10x.h>

void init_bordage(void);
void init_girouette(void);
int get_decalage(void);
int decodeur(void);
void bordage_voiles(int angle_voiles);
