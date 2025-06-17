#include "stm32f10x.h"                  // Device header


void PWM_A0_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 100-1;         // arr
	TIM_InitStructure.TIM_Prescaler = 720-1;       // psc              
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
	
	TIM_OCInitTypeDef OC_InitStructure;
	TIM_OCStructInit(&OC_InitStructure);
	OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	OC_InitStructure.TIM_Pulse = 0;   //ccr
	TIM_OC1Init(TIM2, &OC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
	
}

void PWM_SetCompareA0(uint16_t Compare){
	TIM_SetCompare1(TIM2, Compare);
}



void PWM_A1_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 20000-1;         // arr
	TIM_InitStructure.TIM_Prescaler = 72-1;       // psc              
	TIM_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
	
	TIM_OCInitTypeDef OC_InitStructure;
	TIM_OCStructInit(&OC_InitStructure);
	OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
	OC_InitStructure.TIM_Pulse = 0;   //ccr
	TIM_OC2Init(TIM2, &OC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
	
}

void PWM_SetCompareA1(uint16_t Compare){
	TIM_SetCompare2(TIM2, Compare);
}
