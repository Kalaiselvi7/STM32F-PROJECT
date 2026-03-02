#include<stm32f401xe.h>
#include<stdint.h>
#include<stdio.h>

#define GPIOAEN (0x1UL<<0U)     //unsigned long and unsigned
#define GPIOBEN (0x1UL<<1U)

#define RS (1<<12)
#define RW (1<<14)
#define EN (1<<15)

void GPIO_init();
void TIM2_INPUT_CAPTURE();

void delay(int ms);
void send_cmd(char a);
void send_data(char b);
void display_string(char* str);
void lcd_init();



int main()
{
	char result[50];
	int cap;
	cap =TIM2->CCR1;
	GPIO_init();
	lcd_init();
	TIM2_INPUT_CAPTURE();
	send_cmd(0x80);
	display_string("CAPTURED VALUE");

	while(1)
	{
		send_cmd(0xc0);
		sprintf(result,"%04lu",cap);
		display_string(result);
	}
}
void TIM2_INPUT_CAPTURE()
{
    GPIOB->MODER |= (1<<7);
    GPIOB->AFR[0] |= (1<<13);  //timer2 and channel 2
    GPIOB->AFR[0] |= (1<<12);

    GPIOB->PUPDR |= (1<<7);

    //timer 2 configuration
    RCC->APB1ENR |= (1<<0);
    TIM2->PSC = 16000 - 1;
    TIM2->ARR = 1000;
    TIM2->CNT = 0;
    TIM2->CR1   |= (1<<0);

    TIM2->CCMR1 |= (9<<1);           //timer2, channel 2
    TIM2->CCER  |= (1<<0);            //capture enable
}
void lcd_init()
{
	send_cmd(0x38);
	send_cmd(0x0E);
	send_cmd(0x01);// clear display screen
	send_cmd(0x06);
}
void GPIO_init()
{
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOBEN;
	GPIOA->MODER |= 0x00005555; //output
	GPIOB->MODER |= (1<<3);  //alternate function so (10)
}
void send_cmd(char a)
{
	GPIOA->ODR = a;
	GPIOA->ODR &= ~RS; //RS = 0
	GPIOA->ODR &= ~RW; //RW = 0
	GPIOA->ODR |=  EN;//EN = 1
	delay(5);
	GPIOA->ODR &=  ~EN;//EN =0
}
void send_data(char b)
{
	GPIOA->ODR = b;
	GPIOA->ODR |= RS;
	GPIOA->ODR &= ~RW;
	GPIOA->ODR |=  EN;
	delay(10);
	GPIOA->ODR &=  ~EN;
}
void display_string(char* str)
{
	while(*str)
	{
		send_data(*str++);
	}
}
void delay(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
	for(j=0;j<1000;j++);
}
