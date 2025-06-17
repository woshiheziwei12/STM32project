#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"
void SERVO_Init(void)
{
	PWM_B0_Init();
}
void SERVO_SetAngle(float angle)
{ // 500 是0   2500是1800
	PWM_SetCompareB0(angle * 2000 / 180 + 500);
}
