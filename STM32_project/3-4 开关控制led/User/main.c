#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "key.h"
int main (void) 
{
	uint8_t key_Value = 0;
	LED_A1_A2_Init();
	KEY_B1_B11_Init();
	while (1) {
		key_Value = READ_Key_Value();
		if (key_Value == 1)
		{
			LED_A1_Turn();
		}
		if (key_Value == 2)
		{
			LED_A2_Turn();
		}
	}
}

