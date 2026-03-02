#include<stdint.h>
#define PERI_BASE (0x40000000)

#define AHB1_OFFSET (0x20000)
#define AHB1_BASE   (AHB1_OFFSET + PERI_BASE)  // 0X4002 0000

#define GPIOA_OFFSET (0x00)
#define GPIOA_BASE  (GPIOA_OFFSET + AHB1_BASE) // 0X4002 0000

#define RCC_OFFSET (0x3800)
#define RCC_BASE   (RCC_OFFSET + AHB1_BASE)   // 0X4002 3800


typedef struct
{
	volatile uint32_t CR;        //0X00
	volatile uint32_t PLLCFGR;   //0X04
	volatile uint32_t CFGR;      //0X08
	volatile uint32_t CIR;       //0X0C
	volatile uint32_t AHB1RSTR;  //0X10
	volatile uint32_t AHB2RSTR;  //0X14
	volatile uint32_t DUMMY1[2];
	volatile uint32_t APB1RSTR;  //0X20
	volatile uint32_t APB2RSTR;  //0X24
	volatile uint32_t DUMMY2[2];
	volatile uint32_t AHB1ENR;   //0X30
	volatile uint32_t AHB2ENR;
	volatile uint32_t DUMMY3[2];
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t DUMMY4[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t DUMMY5[2];
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t DUMMY6[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t DUMMY7[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t DUMMY8;
	volatile uint32_t DCKCFGR;
}RCC_TYPEDEF;


typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDER;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
}GPIO_TYPEDEF;

typedef struct
{
	volatile uint32_t TIMx_CR1;  //0X00
	volatile uint32_t TIMx_CR2;  //0X04
	volatile uint32_t TIMx_SMCR;
	volatile uint32_t TIMx_DIER;
	volatile uint32_t TIMx_SR;
	volatile uint32_t TIMx_EGR;
	volatile uint32_t TIMx_CCMR1;
	volatile uint32_t TIMx_CCMR2;
	volatile uint32_t TIMx_CCER;
	volatile uint32_t TIMx_CNT;
	volatile uint32_t TIMx_PSC;
	volatile uint32_t TIMx_ARR;
	volatile uint32_t DUMMY1;
	volatile uint32_t TIMx_CCR1;
	volatile uint32_t TIMx_CCR2;
	volatile uint32_t TIMx_CCR3;
	volatile uint32_t TIMx_CCR4;
	volatile uint32_t TIMx_DUMMY2;
	volatile uint32_t TIMx_DCR;
	volatile uint32_t TIMx_DMAR;
	volatile uint32_t TIM2_OR;
	volatile uint32_t TIM5_OR;  //0x50

}TIMER_TYPEDEF;

#define RCC ((RCC_TYPEDEF*)RCC_BASE)
#define GPIOA ((GPIO_TYPEDEF*)GPIOA_BASE)
#define TIM2_BASE 0x40000000
#define TIM2 ((TIMER_TYPEDEF*)TIM2_BASE)

void TIM2_INIT();
int main()
{
	RCC->AHB1ENR |= (1<<0);

	/*GPIOA->MODER |= (1<<0);
	GPIOA->MODER |= (1<<2);
	GPIOA->MODER |= (1<<4);
	GPIOA->MODER |= (1<<6);
	GPIOA->MODER |= (1<<8);
	GPIOA->MODER |= (1<<10);
	GPIOA->MODER |= (1<<12);
	GPIOA->MODER |= (1<<14);
	GPIOA->MODER |= (1<<16);*/
	GPIOA->MODER &= ~0xFFFF;  // clear MODE for PA0–PA7
	GPIOA->MODER |=  0x5555;  // set PA0–PA7 to OUTPUT (01 01 01 ...)


	while(1)
	{
		GPIOA->ODR = 0xffff;
		TIM2_INIT();

		GPIOA->ODR = 0x00;
		TIM2_INIT();
	}
}
void TIM2_INIT()
{
	RCC->APB1ENR |= (1<<0);
	TIM2->TIMx_PSC = 1600-1;
	TIM2->TIMx_CNT = 0;
	TIM2->TIMx_ARR = 800;

	TIM2->TIMx_CR1 |= (1<<0);          // CEN bit on

	while(!(TIM2->TIMx_SR & 1));       // UIF = bit0
	TIM2->TIMx_SR &= ~(1);             // clear UIF

}

























