#include"stm32f401xe.h"

void EXTI9_5_IRQHandler(void);

void ex_int();
int main()
{
	RCC->AHB1ENR |= (1<<1);

	GPIOB->MODER &= ~(0x3 << 12); // clear first
	GPIOB->MODER |=  (0x1 << 12); // set output


	GPIOB->MODER &= ~(0x3<<10);   //input
	GPIOB->PUPDR |= (1<<10);

	ex_int();

	while(1);

}
void EXTI9_5_IRQHandler(void)

{
	// Check if interrupt is from pin PB5
	if(EXTI->PR & EXTI_PR_PR5)
	{
		EXTI->PR |= EXTI_PR_PR5; // clear flag
		GPIOB->ODR ^= (1<<6);   //USING XOR for toggle LED
	}
}
void ex_int()
{
	RCC->APB2ENR |= (1<<14);  //enable system configuration controller clock enable bit 14

	SYSCFG->EXTICR[1] |= (0x1<<4);  //system will give 0,1,2,3,4,5 so our pin 5

	//external interrupt registers
	EXTI->IMR  |= (0x1<<5);  //unmasked using external interrupt register pin 5

	EXTI->FTSR |= (0x1<<5);  //triggered in falling edge bec we using pull-up so
	NVIC_EnableIRQ(EXTI9_5_IRQn);

}
