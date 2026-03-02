#include<stm32f401xe.h>
#define RS (1<<8)
#define RW (1<<9)
#define EN (1<<10)
#define R1 (1<<0)
#define R2 (1<<1)
#define R3 (1<<2)
#define R4 (1<<3)
#define C1 (1<<4)
#define C2 (1<<5)
#define C3 (1<<6)
#define C4 (1<<7)

void delay(int ms);
void lcd_init();
void send_cmd(char a);
void send_data(char b);
void display_string(char* str);
void keypad();
void row1();
void row2();
void row3();
void row4();

int main()
{
	RCC->AHB1ENR |= (1<<0);
	//RCC->AHB1ENR |= (1<<1);
	RCC->AHB1ENR |= (1<<2);

	GPIOA->MODER |= (1<<0); //output
	GPIOA->MODER |= (1<<2);
	GPIOA->MODER |= (1<<4);
	GPIOA->MODER |= (1<<6);

	GPIOA->MODER &= ~(1<<8);      //input
	GPIOA->MODER &= ~(1<<9);
	GPIOA->MODER &= ~(1<<10);
	GPIOA->MODER &= ~(1<<11);
	GPIOA->MODER &= ~(1<<12);
	GPIOA->MODER &= ~(1<<13);
	GPIOA->MODER &= ~(1<<14);
	GPIOA->MODER &= ~(1<<15);

	GPIOA->PUPDR |= (1<<8);   //pullup
	GPIOA->PUPDR |= (1<<10);
	GPIOA->PUPDR |= (1<<12);
	GPIOA->PUPDR |= (1<<14);

	GPIOC->MODER &= ~(1<<16);
	GPIOC->MODER &= ~(1<<18);
	GPIOC->MODER &= ~(1<<20);

	GPIOC->MODER |= (1<<16);
	GPIOC->MODER |= (1<<18);
	GPIOC->MODER |= (1<<20);

	GPIOC->MODER |= 0x5555;  //output

	lcd_init();

	while(1)
	{
		send_cmd(0x80);
		display_string("Enter the number");
		delay(60);
		send_cmd(0xc0);
		keypad();
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
	GPIOC->ODR = a;
	GPIOC->ODR &= ~RS; //RS = 0
	GPIOC->ODR &= ~RW; //RW = 0
	GPIOC->ODR |=  EN;//EN = 1
	delay(5);
	GPIOC->ODR &=  ~EN;//EN =0
}
void send_data(char b)
{
	GPIOC->ODR = b;
	GPIOC->ODR |= RS;
	GPIOC->ODR &= ~RW;
	GPIOC->ODR |=  EN;
	delay(10);
	GPIOC->ODR &=  ~EN;
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
	for(j=0;j<2000;j++);
}
void keypad()
{
	row1();
	row2();
	row3();
	row4();
}
void row1()
{
   GPIOA->ODR &= ~R1;
   GPIOA->ODR |= (R2|R3|R4);

   if(!(GPIOA->IDR & C1))
   {
	   send_data('7');
	   while(!(GPIOA->IDR & C1));
	}
    else if(!(GPIOA->IDR & C2))
     {
  	   send_data('8');
  	   while(!(GPIOA->IDR & C2));
  	}
    else if(!(GPIOA->IDR & C3))
       {
     	  send_data('9');
     	   while(!(GPIOA->IDR & C3));
     	}
    else if(!(GPIOA->IDR & C4))
          {
         	send_data('/');
            while(!(GPIOA->IDR & C4));
         }
}
void row2()
{
   GPIOA->ODR &= ~R2;
   GPIOA->ODR |= (R1|R3|R4);

   if(!(GPIOA->IDR & C1))
   {
	   send_data('4');
	   while(!(GPIOA->IDR & C1));
	}
    else if(!(GPIOA->IDR & C2))
     {
  	   send_data('5');
  	   while(!(GPIOA->IDR & C2));
  	}
    else if(!(GPIOA->IDR & C3))
       {
     	  send_data('6');
     	   while(!(GPIOA->IDR & C3));
     	}
    else if(!(GPIOA->IDR & C4))
          {
         	send_data('*');
            while(!(GPIOA->IDR & C4));
         }
}
void row3()
{
   GPIOA->ODR &= ~R3;
   GPIOA->ODR |= (R1|R2|R4);

   if(!(GPIOA->IDR & C1))
   {
	   send_data('1');
	   while(!(GPIOA->IDR & C1));
	}
    else if(!(GPIOA->IDR & C2))
     {
  	   send_data('2');
  	   while(!(GPIOA->IDR & C2));
  	}
    else if(!(GPIOA->IDR & C3))
       {
     	  send_data('3');
     	   while(!(GPIOA->IDR & C3));
     	}
    else if(!(GPIOA->IDR & C4))
          {
         	send_data('-');
            while(!(GPIOA->IDR & C4));
         }
}
void row4()
{
   GPIOA->ODR &= ~R4;
   GPIOA->ODR |= (R1|R2|R3);

   if(!(GPIOA->IDR & C1))
   {
	 send_cmd(0x01);
	 while(!(GPIOA->IDR & C1));
	}
   else if(!(GPIOA->IDR & C2))
    {
  	 send_data('0');
  	 while(!(GPIOA->IDR & C2));
  	}
    else if(!(GPIOA->IDR & C3))
    {
     send_data('=');
     while(!(GPIOA->IDR & C3));
    }
    else if(!(GPIOA->IDR & C4))
     {
      send_data('+');
      while(!(GPIOA->IDR & C4));
      }
}


























