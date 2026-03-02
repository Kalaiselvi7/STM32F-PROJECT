#include<stm32f401xe.h>
#define RS (1<<0)
#define RW (1<<1)
#define EN (1<<2)

void delay(int ms);
void send_cmd(char a);
void send_data(char b);
void display_string(char* str);
void lcd_init();

int main()
{
	RCC->AHB1ENR |= (1<<0);
	RCC->AHB1ENR |= (1<<1);

	GPIOA->MODER |= 0x5555; //output

	// Clear PB0
	GPIOB->MODER |=  (0x1 << 0);  // Set PB0 as output

	GPIOB->MODER |=  (0x1 << 2);  // PB1

	GPIOB->MODER |=  (0x1 << 4); // PB2



	lcd_init();

	while(1)
	{

		send_cmd(0x80);
		display_string("kalai");
		delay(1000);
		send_cmd(0xc0);
		display_string("Embedded");
		delay(1000);
		send_cmd(0x01);
		delay(100);
	}
}
void lcd_init()
{
	send_cmd(0x38);
	send_cmd(0x0E);
	send_cmd(0x01);// clear display screen
	send_cmd(0x06);
}
void send_cmd(char a)
{
	GPIOA->ODR = a;
	GPIOB->ODR &= ~RS; //RS = 0
	GPIOB->ODR &= ~RW; //RW = 0
	GPIOB->ODR |=  EN;//EN = 1
	delay(5);
	GPIOB->ODR &=  ~EN;//EN =0
}
void send_data(char b)
{
	GPIOA->ODR = b;
	GPIOB->ODR |= RS;
	GPIOB->ODR &= ~RW;
	GPIOB->ODR |=  EN;
	delay(500);
	GPIOB->ODR &=  ~EN;
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
	for(j=0;j<5000;j++);
}
