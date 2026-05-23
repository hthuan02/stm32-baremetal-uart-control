#ifndef __USART_H__
#define __USART_H__

#include "sys_stm32f10x.h"              

#if (BUFFER_SIZE & (BUFFER_SIZE - 1)) != 0
#error "BUFFER_SIZE must be power of 2"
#endif

void USART2_Config(void);
void USART2_SendChar(uint8_t c);
void USART2_SendString(const char *str);

#endif // __USART_H__
    