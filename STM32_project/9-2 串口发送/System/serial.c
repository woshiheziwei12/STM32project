#include "stm32f10x.h"                  // Device header
#include "serial.h"

void Serial_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}


void Serial_SendByte(uint8_t byte)
{
	USART_SendData(USART1, byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}

void Serial_SendArray(uint8_t *byte, uint16_t length)
{
	for (int i = 0;i < length;i++) {
		Serial_SendByte(byte[i]);
	}
}

void Serial_SendString(char *string)
{
	for (int i = 0;string[i] != 0;i++) {
		Serial_SendByte(string[i]);
	}
}

uint32_t Serial_Power(uint32_t X,uint32_t Y)
{
	uint32_t ans = 1;
	while(Y!=0)
	{
		Y--;
		ans *= X;
	}
	return ans;
}

void Serial_SendNum(uint32_t number, uint8_t length)
{
	for(int i = 0;i<length;i++)
	{
		Serial_SendByte(number / Serial_Power(10, length-i-1) % 10);
	}
}

int fputc(int ch, FILE* f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char string[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(string, format, arg);
	va_end(arg);
	Serial_SendString(string);
}


