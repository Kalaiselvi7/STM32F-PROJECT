#include<stm32f401xe.h>
                                           //TIMER2 - CHANNEL 3
void TIM2_OUTPUT_COMPARE();

int main()
{
	TIM2_OUTPUT_COMPARE();
	while(1);

}
void TIM2_OUTPUT_COMPARE()
{
	//BUS FOR COMPARE
	RCC->AHB1ENR |=(1<<0);
	GPIOA->MODER |= (1<<5);
	GPIOA->AFR[0] |= (1<<8);


	//TIMER2 CONFIGURE
	RCC->APB1ENR |= (1<<0);
	TIM2->PSC =1600-1;
	TIM2->CNT = 0;
	TIM2->CR1 |= (1<<0);
	TIM2->ARR = 2000;

	//COMPARE CONFIGURE
	TIM2->CCMR2 |= (0X3UL << 4U);

	TIM2->CCER  |= (1<<8);
	TIM2->CCR3 = 1000;
}
