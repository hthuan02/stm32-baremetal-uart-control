#include "gpio.h"

void GPIO_Config(void)
{	
	/* Enable clock for port A */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	/* Set PA2 PA3 (TX RX) USART2 */
	GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
	GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
	
	/* Set up PA2 - TX */
	// MODE2 TX - Output 2MHz (01)
	GPIOA->CRL |= GPIO_CRL_MODE2_0;

	// CNF2 TX - AF Push pull (10)
	GPIOA->CRL |= GPIO_CRL_CNF2_1;
	
	/* Set up PA3 - RX */
	// MODE3 RX - Input 00: Tu dong mac dinh, khong can config MODE
	// CNF3 RX - Input pull up (10), USART khong dung pull down (Trang thai IDLE cua TX,RX = 1)
	GPIOA->CRL |= GPIO_CRL_CNF3_1;
	GPIOA->ODR |= (1U << 3);
	
	/* Set PA10 (I/O) LED Control */
	GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
	GPIOA->CRH |= GPIO_CRH_MODE10;
}

/* ACTIVE LOW - LED OFF*/
void LED_ON(void)
{
	GPIOA->ODR &= ~(1U << 10);
}


void LED_OFF(void)
{
	GPIOA->ODR |= (1U << 10);
}
