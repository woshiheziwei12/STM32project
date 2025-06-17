#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "serial.h"
uint8_t keyNum = 0;
int main (void) 
{
	Serial_Init();
	Serial_SendString("你好");
	while (1) {
		
	}
}
