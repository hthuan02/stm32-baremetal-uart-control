#include "uart.h"

void USART2_Config(void)
{	
	/* Enable clock for USART2 */
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	/* 0. Disable USART2 */
	USART2->CR1 &= ~USART_CR1_UE;
	
	/* 1. Baudrate config */ 
	/** Config baudrate trên IDE Keil C
	 * 	USARTDIV = FCLK / (16 * Baud) = 36Mhz / (16 * 9600) = 234,375
	 *  - FCLK: 36MHz (APB1)
	 *  - Oversampling STM32F10x = 16, Baud choice = 9600
	 *  - Mantissa [15:4] (so nguyen) = 234
	 *  - Fraction [3:0] (thap phan) = 0,375 * 16 = 6
	 *  - BRR = Mantissa << 4 | Fraction = (234 << 4) | 6 = 3744 | 6 = 3750
	 */

	/* Config Baudrate với hệ thống tự viết startup file & linker script
	 * Vì trong hàm Reset Handler gọi thẳng vào main(), mà không config clock
     * - Nên sau Reset Handler, stm32f103 sẽ chạy xung nội mặc định HSI = 8Mz
	 * - bus APB1 cấp cho USART2 cũng chạy 8Mhz
	 *  
	 * USARTDIV = FCLK / (16 * Baud) = 8Mhz / (16 * 9600) = 52.0833
	 * ...
	 * --> BRR: 833
	 */
	USART2->BRR = 833;
	
	/* 2. Data frame (data, parity, stop bit) */
	// Data (M = 0, 8bit)
	USART2->CR1 &= ~USART_CR1_M;

	// Parity (khong su dung parity bit)
	USART2->CR1 &= ~USART_CR1_PCE;

	// Stop (00 = 1 stop bit)
	USART2->CR2 &= ~USART_CR2_STOP;
	
	/* 3. Enable TX - RX */
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;

	/* 4. Enable RXNE interrupt */
	USART2->CR1 |= USART_CR1_RXNEIE;
	
		/* Enable USART2 interrupt in NVIC */
	NVIC_EnableIRQ(USART2_IRQn);

	/* Set interrupt priority (Do uu tien ngat)*/ 
	NVIC_SetPriority(USART2_IRQn, 1);

	/* 6. Enable USART2 */
	USART2->CR1 |= USART_CR1_UE;
	
	// Xoa du lieu rac ban dau
	volatile uint16_t dummy;
	dummy = USART2->SR;
	dummy = USART2->DR;
	(void)dummy;
}

/* Hàm gửi kí tự */
void USART2_SendChar(uint8_t c)
{	
	// Chờ cờ TXE = 1 (DR rỗng), thì ghi dữ liệu mới
	while(!(USART2->SR & USART_SR_TXE));	
	USART2->DR = c;
}

/* Hàm gửi chuỗi (tái sử dụng lại gửi kí tự) */
void USART2_SendString(const char *str)
{
	while(*str)
	{
		USART2_SendChar((uint8_t)*str++);
	}
}


