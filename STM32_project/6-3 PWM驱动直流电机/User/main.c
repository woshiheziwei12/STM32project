#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "motor.h"
uint8_t keyNum = 0;
int main (void) 
{
	MOTOR_Init();
	MOTOR_SetSpeed(0);
	while (1) {
		
	}
}
