#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "timer.h"
#include "OLED.h"
uint8_t ultrasonic_DelayFlag = 0;
void Ultrasonic_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;   //TRIG
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;   //ECHO
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	Timer4_Init();
	
}
float Ultrasonic_TestDistance()
{
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1);
	if(ultrasonic_DelayFlag == 1) { // 启动小汽车电机后，超声波模块莫名其妙短时间不能用了。需要Delay一段时间
		Delay_ms(1500);
		ultrasonic_DelayFlag = 0;
	}
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	Delay_us(20);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == RESET);
	TIM_SetCounter(TIM4,0);
	TIM_Cmd(TIM4,ENABLE);
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == SET);
	TIM_Cmd(TIM4,DISABLE);
	
	uint32_t CNT = TIM_GetCounter(TIM4);
	float distance = (CNT * 1.0 / 10 * 0.34) / 2;
	TIM_SetCounter(TIM4,0);
	Delay_ms(100);
	return distance;
}
