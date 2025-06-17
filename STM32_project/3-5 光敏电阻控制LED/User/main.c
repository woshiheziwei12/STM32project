#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "key.h"
#include "light_sensor.h"
#include "buzzer.h"
int main (void) 
{
	BUZZER_B12_Init();
	Light_Sensor_B13_Init();
	while (1) {
		if(Light_Sensor_B13_Read() == 1) {
			BUZZER_B12_On();
		} else {
			BUZZER_B12_Off();
		}
	}
}

