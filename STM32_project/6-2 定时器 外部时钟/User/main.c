#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "ext_timer.h"
uint32_t timerNum = 0;
int main (void) 
{
	OLED_Init();
	ExtTimer_Init();
	OLED_ShowString(1,1,"time:");
	OLED_ShowString(2,1,"count:");
	
	while (1) {
		OLED_ShowSignedNum(1,6,timerNum, 5);
		
		OLED_ShowSignedNum(2,7,ExtTimer_GetCount(), 5);
	}
}

void TIM2_IRQHandler(void) {
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)== SET) {
		timerNum++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

