#include<stm32f401xe.h>

#define USART2_BAUDRATE 9600

void USART2_TX_RX_INIT()
	{
	    RCC->AHB1ENR |= (1<<0);    // GPIOA clock
	    RCC->APB1ENR |= (1<<17);   // USART2 clock

	    // PA2 & PA3 Alternate Function
	    GPIOA->MODER &= ~(3<<4);
	    GPIOA->MODER |=  (2<<4);
	    GPIOA->MODER &= ~(3<<6);
	    GPIOA->MODER |=  (2<<6);

	    // AF7 for USART2
	    GPIOA->AFR[0] |= (7<<8);   // PA2 TX
	    GPIOA->AFR[0] |= (7<<12);  // PA3 RX

	    // Baud rate
	    USART2->BRR = 16000000 / USART2_BAUDRATE;  //16,000,000 / 9,600 = 1666.66 ticks need to wait for 1 clock pulse

	    USART2->CR1 |= (1<<3);   // TE
	    USART2->CR1 |= (1<<2);   // RE
	    USART2->CR1 |= (1<<13);  // UE
	}

void USART2_write(char a)
{
	USART2->DR = a;
	while(!(USART2->SR & USART_SR_TXE));
}
char USART2_read()
{
	while(!(USART2->SR & USART_SR_RXNE));
	return USART2->DR;
}
int main()
{
	USART2_TX_RX_INIT();

	USART2_write('K');

	while(1)
	{


		for (int i = 0; i < 100000; ++i);
		char receive = USART2_read();

			USART2_write(receive);
	}
}


















