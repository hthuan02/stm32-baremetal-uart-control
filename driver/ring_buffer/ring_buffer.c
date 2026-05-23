#include "ring_buffer.h"

void RingBuffer_Write(Buffer_t *p, uint8_t data)
{	
	// Ghi dữ liệu trước, cập nhật sau
	// uint16_t next_head = (p->head + 1) % BUFFER_SIZE;
	// Thay `%` trên bằng toán tử `&`, để tăng tốc độ x10 lần 
	uint16_t next_head = (p->head + 1) & (BUFFER_SIZE - 1);
	
	if (next_head != p->tail)
	{	
		p->rx_buffer[p->head] = data; 
		p->head = next_head;
	}
}

uint8_t RingBuffer_Read(Buffer_t *p)
{
	uint8_t value = 0;
	volatile uint16_t temp_head = p->head; // Tạo biến tạm tránh lỗi biến gốc	
	
	if (temp_head != p->tail)
		{
		value = p->rx_buffer[p->tail];
		p->tail = (p->tail + 1) & (BUFFER_SIZE - 1);
	}

	return value;
}

uint8_t RingBuffer_Available(Buffer_t *p)
{
	return (p->head != p->tail);
}

/* USART2 Interrupt Service Routine */
void USART2_IRQHandler(void)
{
	/* Kiem tra ngat nhan du lieu */
	if ((USART2->SR & USART_SR_RXNE) && (USART2->CR1 & USART_CR1_RXNEIE))
	{
		uint8_t rx_data = (uint8_t)USART2->DR;

		RingBuffer_Write(&uart_rx_buffer, rx_data);
	}
	
	/* Chuẩn đoán xử lý lỗi (ORE, NE, FE, PE) */
	if (USART2->SR & (USART_SR_ORE | USART_SR_NE | USART_SR_FE | USART_SR_PE))
	{
		volatile uint32_t clear_error;
		clear_error = USART2->SR;
		clear_error = USART2->DR;
		(void)clear_error; 
	}
}

