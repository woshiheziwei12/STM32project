#ifndef __SERIAL_H_
#define __SERIAL_H_
#include <stdio.h>
#include <stdarg.h>

void Serial_Init(void);
void Serial_SendByte(uint8_t byte);
void Serial_SendArray(uint8_t *byte, uint16_t length);
void Serial_SendString(char *string);
uint32_t Serial_Power(uint32_t X,uint32_t Y);
void Serial_SendNum(uint32_t number, uint8_t length);
int fputc(int ch, FILE* f);
void Serial_Printf(char *format, ...);

#endif

