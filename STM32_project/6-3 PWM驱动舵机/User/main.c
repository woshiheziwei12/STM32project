#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "servo.h"
#include "key.h"
uint8_t keyNum = 0;
int main (void) 
{
	float angle = 90;
	OLED_Init();
	SERVO_Init();
	KEY_B1_B11_Init();
	SERVO_SetAngle(90);
	while (1) {
		
	}
}
