#include "stm32f401xe.h"

void TIM2_INIT();
void OC_SET();
void OC_RESET();

int main()
{
    TIM2_INIT();

    while(1)
    {
        OC_SET();
        //for(int i=0;i<1000;i++);

        OC_RESET();
        //for(int i=0;i<500000;i++);
    }
}

void TIM2_INIT()
{
    RCC->AHB1ENR |= (1<<0);   // Enable GPIOA
    RCC->APB1ENR |= (1<<0);   // Enable TIM2

    // PA0 -> AF1 (TIM2_CH1)
    //GPIOA->MODER &= ~(3<<0);
    GPIOA->MODER |=  (2<<0);

   // GPIOA->AFR[0] &= ~(0xF<<0);
    GPIOA->AFR[0] |=  (1<<0);

    TIM2->PSC = 16000 - 1;  // 1ms
    TIM2->ARR = 1000;       // 2 seconds

    TIM2->CNT = 0;      // match at 1 second
    TIM2->CCER |= (1<<0);   // Enable CH1 output
    TIM2->CR1 |= (1<<0);    // Start timer
}

// Output forced HIGH when compare match
void OC_SET()
{
    TIM2->CCMR1 &= ~(7<<4);
    TIM2->CCMR1 |=  (5<<4);   // OC1M = 101 → Force Active
    TIM2->CCR1 = 500;
    while(!(TIM2->SR & TIM_SR_UIF));
    TIM2->SR &= ~(TIM_SR_UIF);
}

// Output forced LOW when compare match
void OC_RESET()
{
    TIM2->CCMR1 &= ~(7<<4);
    TIM2->CCMR1 |=  (4<<4);   // OC1M = 100 → Force Inactive
    TIM2->CCR1 = 600;
    while(!(TIM2->SR & TIM_SR_UIF));
    TIM2->SR &= ~(TIM_SR_UIF);
}
