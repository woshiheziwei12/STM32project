#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "serial.h"
extern char Serial_String[100];
extern int32_t Serial_flag;
uint8_t keyNum = 0;
int main (void) 
{
	Serial_Init();
	OLED_Init();
	while (1) {
		if (Serial_flag == -2) {
			OLED_ShowString(1,1,"            ");
			OLED_ShowString(1,1,Serial_String);
			Serial_SendString(Serial_String);
			Serial_flag = -1;
		}
		
	}
}
