#ifndef __UART_H__
#define __UART_H__

extern void Uart1_Init();
extern void Uart1_SendChar(unsigned char ch);
extern void Uart1_SendString(unsigned char *str);

#endif
