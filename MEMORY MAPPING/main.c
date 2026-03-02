//(instead of header file we used to define)

#define PERI_BASE  (0x40000000UL)

#define AHB1_OFFSET  (0x20000UL)
#define AHB1_BASE  (PERI_BASE  + AHB1_OFFSET)  // 0X4002 0000

#define GPIOA_OFFSET  (0x00UL)
#define GPIOA_BASE  (AHB1_BASE + GPIOA_OFFSET) // 0X4002 0000

#define RCC_OFFSET  (0x3800UL)
#define RCC_BASE  (AHB1_BASE + RCC_OFFSET)     // 0X4002 3800

#define AHB1ENR_OFFSET  (0X30UL)
#define RCC_AHB1ENR  (*(volatile unsigned int *) (RCC_BASE + AHB1ENR_OFFSET)) // 0X 4002 3830  - 0B 0100 0000 0000 0010 0011 1000 0011 0000


#define MODER_OFFSET  (0X00UL)
#define GPIOA_MODER  (*(volatile unsigned int *) (GPIOA_BASE + MODER_OFFSET)) // 0X 4002 0000
#define ODR_OFFSET  (0X14UL)
#define GPIOA_ODR  (*(volatile unsigned int *) (GPIOA_BASE + ODR_OFFSET)) // 0X 4002 0014)


#define GPIOAEN (1<<0)
void delay();
int main()
{
	RCC_AHB1ENR |= GPIOAEN;// (1<<0)

	GPIOA_MODER |= (0x1<<0);
	GPIOA_MODER |= (0x1<<2);
	GPIOA_MODER |= (0x1<<4);
	GPIOA_MODER |= (0x1<<6);
	GPIOA_MODER |= (0x1<<8);
	GPIOA_MODER |= (0x1<<10);
	GPIOA_MODER |= (0x1<<12);
	GPIOA_MODER |= (0x1<<14);

	while(1)
	{
	  GPIOA_ODR = 0XFF;
          delay();
          GPIOA_ODR =0X00;
          delay();
	}
}
void delay()
{
 for(int i=0;i<500000;i++);
}
