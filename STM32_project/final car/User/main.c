#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "serial.h"
#include "car.h"
#include "ultrasonic.h"
#include "servo.h"
#include "infrared.h"
extern char Serial_String[100];
extern int32_t Serial_flag;
extern uint8_t Serial_RxData;
extern uint8_t ultrasonic_DelayFlag;
uint8_t keyNum = 0;
uint8_t angle = 90;
uint8_t ifSetInfraredSignal = 0;

void Main_dual_signal(void)
{
	OLED_ShowHexNum(1,1, Serial_RxData,3);
	OLED_ShowSignedNum(1,11, Serial_flag,3);
	if (Serial_flag == -2) {  // 来自蓝牙的信号
		angle = 90;
		SERVO_SetAngle(angle);
		if (Serial_RxData == 0x20) { // 直行
			Car_GoHead();
		} else if(Serial_RxData == 0x21) { // 左转
			Car_GoLeft();
		} else if(Serial_RxData == 0x22) { // 右转
			Car_GoRight();
		} else if(Serial_RxData == 0x23) { // 原地左转
			Car_SelfLeft();
		} else if(Serial_RxData == 0x24) { // 原地右转
			Car_SelfRight();
		} else if(Serial_RxData == 0x25) { // 停车
			Car_Stop();
		} else if(Serial_RxData == 0x26) { // 倒退
			Car_Rollback();
		} else if(Serial_RxData == 0x27) { // 打开，关闭 红外寻路功能
			ifSetInfraredSignal = !ifSetInfraredSignal;
		} else {
			Serial_flag = -1;
			//日志报错
		}
		Serial_SendString(Serial_String);
		Serial_flag = -1; // 等待命令输入
		Delay_s(1);       // 起码执行1s
	} else if (Serial_flag == -3){ // 来自超声波模块的信号
		if(Serial_RxData == 0x30) { //超声波方向有障碍
			Car_Stop();
			angle = angle == 180?0:angle + 90;
			SERVO_SetAngle(angle);
			Delay_s(2);
		} else if(Serial_RxData == 0x31){ //需要右转
			angle = 90;
			SERVO_SetAngle(angle);
			Delay_s(1);
			Car_SelfRight();
			Delay_s(1);
			Car_GoHead();
			Serial_flag = -1;
			ultrasonic_DelayFlag= 1;
			Serial_RxData = 0;
		} else if(Serial_RxData == 0x32) { // 需要左转
			angle = 90;
			SERVO_SetAngle(angle);
			Delay_s(1);
			Car_SelfLeft();
			Delay_s(1);
			Car_GoHead();
			Serial_flag = -1;
			ultrasonic_DelayFlag= 1;
			Serial_RxData = 0;
		} else if(Serial_RxData == 0x33) { // 需要直行
			angle = 90;
			SERVO_SetAngle(angle);
			Car_GoHead();
			Delay_s(1);
			Serial_flag = -1;
			ultrasonic_DelayFlag= 1;
			Serial_RxData = 0;
		} else if(Serial_RxData == 0x34) { // 需要掉头
			angle = 90;
			SERVO_SetAngle(angle);
			Delay_s(1);
			Car_SelfLeft();
			Delay_s(2);
			Car_GoHead();
			Serial_flag = -1;
			ultrasonic_DelayFlag= 1;
			Serial_RxData = 0;
		} else {
			Serial_flag = -1;
		}
	} else if (Serial_flag == -4) { // 来自红外线探测的信号
		angle = 90;
		SERVO_SetAngle(angle);
		if(Serial_RxData == 0x40) { //直行
			Car_GoHead();
		} else if(Serial_RxData == 0x41){ //停车
			Car_Stop();
		} else if(Serial_RxData == 0x42) { // 需要左转
			Car_GoLeft();
		} else if(Serial_RxData == 0x43) { // 需要右转
			Car_GoRight();
		} else if(Serial_RxData == 0x44) { // 需要原地左转
			Car_SelfLeft();
		} else if(Serial_RxData == 0x45) { // 需要原地右转
			Car_SelfRight();
		} else {
			//日志报错
		}
		Serial_flag = -1;
	}
		
}

void Main_SetInfraredSignal(){
	uint8_t a12, a15, b1, b4;
	a12 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12);
	a15 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15);
	b1 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1);
	b4 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4);
	OLED_ShowNum(2,1, a12,3);
	OLED_ShowNum(2,5, a15,3);
	OLED_ShowNum(3,1, b1,3);
	OLED_ShowNum(3,5, b4,3);
	if((a12 == SET && a15 == SET && b4 == SET && b1 == SET) || Serial_flag == -3) {
		
	} else {
		Serial_flag = -4;
		if(a12 == SET && a15 == RESET && b4 == RESET && b1 == SET) {
			Serial_RxData = 0x40;
		} else if(a12 == RESET && a15 == RESET && b4 == RESET && b1 == RESET) {
			Serial_RxData = 0x41;
		} else if((a12 == RESET && a15 == RESET && b4 == SET && b1 == SET) || (a12 == SET && a15 == RESET && b4 == SET && b1 == SET)) {
			Serial_RxData = 0x42;  // 需要左转
		} else if((a12 == SET && a15 == SET && b4 == RESET && b1 == SET) || (a12 == SET && a15 == SET && b4 == RESET && b1 == RESET)) {
			Serial_RxData = 0x43;  // 需要右转
		} else if(a12 == RESET) {
			Serial_RxData = 0x44;  // 需要原地左转                                                   
		} else if(b1 == RESET) {
			Serial_RxData = 0x45;  // 需要原地右转
		} else{
			Serial_RxData = 0x00;
		}
		
	}
	
}

void Main_Set_signal()
{   
	if (Serial_flag == -2) {
		return ;
	}
	if (ifSetInfraredSignal == 1) {
		Main_SetInfraredSignal();
	} else {
		uint16_t distance = Ultrasonic_TestDistance();  //获取超声波测距的距离
		OLED_ShowNum(1,5, distance,4);
		if(distance < 15) {
			Serial_flag = -3;
			Serial_RxData = 0x30;
		} else if(Serial_flag == -3) {
			if (angle == 90) {
				Serial_RxData = 0x33;
			} else if(angle == 0) {
				Serial_RxData = 0x31;
			} else if(angle == 180) {
				Serial_RxData = 0x32;
			}
		}
	}
}
int main (void) 
{
	Serial_Init();
	OLED_Init();
	Ultrasonic_Init();
	Car_Init();
	Infrared_Init();
	SERVO_Init();
	SERVO_SetAngle(angle);
	while (1) {
//		Main_Set_signal();
		Main_dual_signal();
	}
}


