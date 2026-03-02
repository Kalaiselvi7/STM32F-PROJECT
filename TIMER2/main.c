#include<stm32f401xe.h>
#include<stdint.h>
#define CEN (1<<0)
#define UIF (1<<0)

void delay();
int main()
{
	RCC->AHB1ENR |= (1<<0);  //2 bus enable
	RCC->AHB1ENR |= (1<<1);

	GPIOA->MODER |= 0x00005555;
	GPIOB->MODER |= 0x00005555;

	while(1)
	{
		GPIOA->ODR |= (0x07);
		delay();
		GPIOA->ODR &= ~(0x07);
		delay();

		GPIOB->ODR |= (0x07);
	    delay();
	    GPIOB->ODR &= ~(0x07);
	    delay();

	}
}
void delay()
{
	RCC->APB1ENR |= (1<<0);   //timer bus enable
	TIM2->PSC = 16000-1;  /* 15999 to calculate the frequency for 1ms,(prescaler its count the pulse
	                       have 15999 pulse)*/
	TIM2->CNT = 0;         //start from 0;
	TIM2->ARR = 200;        //auto reload for 0.2seconds ->100 ms)
	TIM2->CR1 |= CEN ; //CEN (count enable)

	while(!(TIM2->SR & UIF));  //interrupt flag UIF when its comes from 1 overflow then -> while(0)
	TIM2->SR &= ~UIF;         //0

}
