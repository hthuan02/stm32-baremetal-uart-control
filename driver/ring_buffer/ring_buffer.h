#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include "sys_stm32f10x.h"
#include "uart.h"
#define BUFFER_SIZE 64

typedef struct
{
	volatile uint8_t rx_buffer[BUFFER_SIZE];
	volatile uint16_t head;	// write index - same circular queue in DSA
	volatile uint16_t tail; // read index - same circular queue in DSA
} Buffer_t;
extern Buffer_t uart_rx_buffer;

/* Ring Buffer USART Prototype */
void RingBuffer_Write(Buffer_t *p, uint8_t data);
uint8_t RingBuffer_Read(Buffer_t *p);							 
uint8_t RingBuffer_Available(Buffer_t *p); 

/* NVIC for USART Prototype */
void USART2_IRQHandler(void);

#endif // __RING_BUFFER_H__
