#include<stm32f401xe.h>
#define button1 (1<<2)
#define button2 (1<<4)

//void delay();
int main()
{

	RCC->AHB1ENR |= (1<<0);
	RCC->AHB1ENR |= (1<<1);

	GPIOA->MODER &= ~(1<<4);  //0(input)reset
	GPIOA->MODER &= ~(1<<5);

	GPIOB->MODER &= ~(1<<6);
	GPIOB->MODER &= ~(1<<7);


	GPIOB->MODER |= 0x5555;  //1(output)

	GPIOA->PUPDR |= (1<<5);
	GPIOA->PUPDR |= (1<<9);

	while(1)
	{
		if((GPIOA->IDR & button1))
		{
			GPIOB->ODR |= (1<<0);
			GPIOB->ODR |= (1<<1);
		}
		else if((GPIOA->IDR & button2))
		{
			GPIOB->ODR |= (1<<2);
		    GPIOB->ODR |= (1<<3);
		}
		else
		{
			 GPIOB->ODR = 0x00;
		}
	}
}
