#include<stm32f401xe.h>
                                 //TIMER3 - CHANNEL2
void TIM3_OUTPUT();
void DuCy_increament();
void DuCy_decreament();

int main()
{
	TIM3_OUTPUT();
	while(1)
	{
		DuCy_increament();
		for(int i=0;i<10000;i++);
		DuCy_decreament();
		for(int i=0;i<10000;i++);
	}
}
void TIM3_OUTPUT()
{
		RCC->AHB1ENR |= (1<<0);
		RCC->APB1ENR |= (1<<1);

		GPIOA->MODER  |= (0x2<<14);
		GPIOA->AFR[0] |= (0x2<<28);

		TIM3->PSC = 16000-1;
		TIM3->CNT = 0;
		TIM3->ARR = 100;
		TIM3->CR1 = (1<<0);

		TIM3->CCER |= (1<<4);
		TIM3->CCMR1 &= ~(0x7<<12);
		TIM3->CCMR1 |= (0x6<<12);
}
void DuCy_increament()
{
	int i;
	TIM3->CCR2 = 0;
	for(i=0;i<=100;i+=10)
	{
		TIM3->CCR2 = i;
		while(!(TIM3->SR & TIM_SR_UIF));
		TIM3->SR &= ~(TIM_SR_UIF);
	}
}
void DuCy_decreament()
{
	int i;
	TIM3->CCR2 = 100;
	for(i=100;i>=0;i-=10)
	{
		TIM3->CCR2 = i;
		while(!(TIM3->SR & TIM_SR_UIF));
		TIM3->SR &= ~(TIM_SR_UIF);
	}

}











