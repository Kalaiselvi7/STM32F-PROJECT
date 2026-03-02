#include<stm32f401xe.h>
#include <stdint.h>
#include <stdio.h>

#define GPIOAEN (1U << 0)


void ADC_INIT();
void START_CONVERSION(void);
uint32_t ADC_READ(void);

void LED_GPIO();
void LCD_PRINT(char *print);
void DELAY(uint32_t ms);

int main()
{
	int sensor;
	ADC_INIT();
	START_CONVERSION();
	while(1)
	{
	sensor = ADC_READ();

		  if (sensor>2000)
		  {
		     GPIOA->ODR |= 0X1<<5;
		  }
		  else
		  {
		    GPIOA->ODR &= ~(0X1<<5);
		  }
	}
}
void ADC_INIT()
{
	RCC-> AHB1ENR |= (1<<0);  //GPIO A PORT ENBALE

	RCC->APB2ENR |= (1<<8);  //ADC ENABLE

	GPIOA->MODER &= ~(3 << 4);
	GPIOA->MODER |= (0x3<<4);

	//ADC REGISTERS
	ADC1->CR2 |= (1<<0);   //ADCON
    ADC1->SMPR2 |= (0x6<<6);   //clock cycle dividers

    ADC1->SQR3 |= (2<<0); //channel with respective conversion
    ADC1->SQR1 &= ~(0xf<<20);  //length of the converion

}

void START_CONVERSION(void)
{
	ADC1->CR2 |= (1<<1);  //continuos conversion
	ADC1->CR2 |= (1<<30); //ADC conversion start
}

uint32_t ADC_READ(void)
{
	while(!(ADC1->SR & ADC_SR_EOC));

	uint32_t value  = ADC1->DR ; //converted digital voltage stroed in value

	ADC1->SR &= ~(ADC_SR_EOC);

	return value;
}
void LED_GPIO()
{

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= 0X1<<10;
}

void LCD_PRINT(char *print)
{
	while(*print)
	{
		LCD_DATA(*print++);
	}
}

void DELAY(uint32_t ms)
{
	uint32_t i,j;
	for(i=0; i<ms; i++)
		for(j=0; j<16000; j++);
}
















