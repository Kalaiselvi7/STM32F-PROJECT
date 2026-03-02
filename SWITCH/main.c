#include<stm32f401xe.h>
#define button (1<<2)

//void delay();
int main()
{
	RCC->AHB1ENR |= (1<<0);
	RCC->AHB1ENR |= (1<<1);

	GPIOA->MODER &= ~(1<<4);  //0(input)reset
	GPIOA->MODER &= ~(1<<5);

	GPIOB->MODER &= ~(1<<6);
	GPIOB->MODER &= ~(1<<7);
	GPIOB->MODER &= ~(1<<8);
	GPIOB->MODER &= ~(1<<9);

	GPIOB->MODER |= 0x5555;  //1(output)
	GPIOA->PUPDR |= (1<<4);

	while(1)
	{
		if(!(GPIOA->IDR & button))
		{
			GPIOB->ODR = 0xFF;
		}
		else
		{
			GPIOB->ODR = 0x00;
		}
	}
}
