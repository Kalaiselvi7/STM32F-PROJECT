#include<stm32f401xe.h>


#define APB2CLK 16000000
#define USART_BAUDRATE 9600
#define LED (1<<14)

void USART1_TX_RX_INT();
void USART1_write(char a);
char USART1_read();
void USART1_IRQHandler();


void USART1_handler();

int main()
{
	RCC->AHB1ENR  |= (1<<0);     //GPIOA EN
	GPIOA->MODER &= ~(3 << 28);   // clear
	GPIOA->MODER |=  (1 << 28);   // output

    USART1_TX_RX_INT();
    USART1_write('H');

    while(1);

}
void USART1_TX_RX_INT()
{

	RCC->APB2ENR |= (1<<4);  //USART1 ENBALE

	// PA9 → TX
	GPIOA->MODER &= ~(0x3<<18);
	GPIOA->MODER |=  (2<<18);

	// PA10 → RX
	GPIOA->MODER &= ~(3<<20);
	GPIOA->MODER |=  (2<<20);

	// PA9 AF7
	GPIOA->AFR[1] &= ~(0xF << 4);
	GPIOA->AFR[1] |=  (7 << 4);

	// PA10 AF7
	GPIOA->AFR[1] &= ~(0xF << 8);
	GPIOA->AFR[1] |=  (7 << 8);


	 USART1->BRR = APB2CLK/USART_BAUDRATE;

	 USART1->CR1 |= (1<<3);  //transmitter EN
	 USART1->CR1 |= (1<<2);   //receiver EN
	 USART1->CR1 |= (1<<13); // UE: USART enable
	 USART1->CR1 |= (1<<5);   //INTERRUPT EN

	 NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_write(char a)
{
	while(!(USART1->SR & USART_SR_TXE));   //TXE it will wait untill the transmit

	USART1->DR = a;
}

char USART1_read()
{
	while (!(USART1->SR & USART_SR_RXNE));
	return USART1->DR;

}

void USART1_IRQHandler()
{
	if(USART1->SR & USART_SR_RXNE)
	{
		char receive = USART1_read();
		USART1_write(receive);
		GPIOA->ODR ^= LED;
	}
}













