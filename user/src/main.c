#include "gpio.h"
#include "uart.h"
#include "ring_buffer.h"

Buffer_t uart_rx_buffer ={0};

int main(void)
{
	GPIO_Config();
	USART2_Config();

	uint8_t rx_data = 0;
	LED_OFF();
	while(1)
	{
		/* Kiem tra ring buffer co data */
		if (RingBuffer_Available(&uart_rx_buffer))
		{
			rx_data = RingBuffer_Read(&uart_rx_buffer);

			switch (rx_data)
			{
				case 'T':
					LED_OFF();
					USART2_SendString("-LED OFF\r\n");
					break;

				case 'S':
					LED_ON();
					USART2_SendString("-LED ON\r\n");
					break;

				default:
					USART2_SendString("-ERROR\r\n");
					break;
			}
		}
	}
}

