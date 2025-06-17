#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
uint32_t timerNum = 0;
int main (void) 
{
	uint8_t i;
	OLED_Init();
	PWM_A0_Init();
	while (1) {
		for(i = 0;i<= 100; i++) {
			PWD_SetCompareA0(i);
			Delay_ms(10);
		}
		for(i = 0;i<= 100; i++) {
			PWD_SetCompareA0(100-i);
			Delay_ms(10);
		}
	}
}
