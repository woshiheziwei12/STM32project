#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
int main (void) 
{
	OLED_Init();
	
//	OLED_ShowChar(1, 1, 'A');
//	OLED_ShowString(1,3,"hello world!");
//	OLED_ShowNum(2,1, 12345, 5);
//	OLED_ShowSignedNum(2, 7, -66,2);
//	OLED_ShowHexNum(3, 1, 0xAA55, 4);
//  OLED_ShowBinNum(4,1,0xAA55, 16);
	OLED_ShowString(1,6,"ZIWEI!");
	OLED_ShowString(2,7,"LOVE");
	OLED_ShowString(3,5,"MENGMENG!");
	
	while (1) {
		
	}
}

