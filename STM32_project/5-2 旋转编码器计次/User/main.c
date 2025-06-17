#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "encoder.h"
int main (void) 
{
	int32_t encoderNum = 0;
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1,1,"count:");
	
	while (1) {
		encoderNum += Encoder_Getnum();
		OLED_ShowSignedNum(1,7,encoderNum, 5);
	}
}

