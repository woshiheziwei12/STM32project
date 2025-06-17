#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "servo.h"
#include "MOTOR.h"
void Car_Init(void)
{
	SERVO_Init();
	MOTOR_Init();
}
void Car_GoHead() {
	MOTOR_SetA1Speed(70);
	MOTOR_SetA2Speed(70);
}
void Car_Stop() {
	MOTOR_SetA1Speed(0);
	MOTOR_SetA2Speed(0);
}
void Car_GoRight() {
	MOTOR_SetA1Speed(0);
	MOTOR_SetA2Speed(70);
}
void Car_GoLeft() {
	MOTOR_SetA1Speed(70);
	MOTOR_SetA2Speed(0);
}
void Car_SelfRight() {
	MOTOR_SetA1Speed(-70);
	MOTOR_SetA2Speed(70);
}
void Car_SelfLeft() {
	MOTOR_SetA1Speed(70);
	MOTOR_SetA2Speed(-70);
}
void Car_Rollback(void) {
	MOTOR_SetA1Speed(-70);
	MOTOR_SetA2Speed(-70);
}

