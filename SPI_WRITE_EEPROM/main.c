#include<stm32f401xe.h>

void GPIO_INIT();
void SPI2_MASTER_INIT();
void SPI2_BYTE_WRITE();
void SPI2_MOSI(uint8_t b);
void PAGE_STRING(char *ptr);
void PAGE_WRITE();


int main()
{

		uint32_t i;
		SPI2_MASTER_INIT();

		GPIOB->ODR |= (1<<9);//SS=1
		for(i=0;i<1000;i++);
		GPIOB->ODR &= ~(1<<9);//SS=0

		SPI2_MOSI(0X06UL);            //write enable

		GPIOB->ODR |= (1<<9);//SS=1
		for(i=0;i<1000;i++);
		GPIOB->ODR &= ~(1<<9);//SS=0

		SPI2_MOSI(0X02UL);           //write command
		SPI2_MOSI(0X00UL);           //address 16bit so  msb 8 bit
		SPI2_MOSI(0X20UL);           //lsb 8 bit
		SPI2_MOSI('D');              //data

		for(i=0;i<5000;i++);

		SPI2_MOSI('I');
		for(i=0;i<5000;i++);

		SPI2_MOSI('S');              //data

	    for(i=0;i<5000;i++);

		SPI2_MOSI('K');


	    GPIOB->ODR |= (1<<9);//SS=1
	    for(i=0;i<1000;i++);
	    GPIOB->ODR &= ~(1<<9);//SS=0


	    PAGE_WRITE();

	   for(i=0;i<80000;i++);

		SPI2_MOSI(0X04UL);          //write disable
		GPIOB->ODR |= (1<<9);//SS=1


		while(1);

		return 0;

}
void GPIO_INIT()
{
	RCC->AHB1ENR |= (1<<1);

	// PB13, PB14, PB15 → AF5 (SPI2)
	GPIOB->MODER |= (2<<26) | (2<<28) | (2<<30);
	GPIOB->AFR[1] |= (5<<20) | (5<<24) | (5<<28);

	// PB9 → GPIO output (CS)
	GPIOB->MODER |= (1<<18);

}
void SPI2_MASTER_INIT()
{
	RCC->APB1ENR |= (1<<14);  //SPI2

	GPIO_INIT();

	SPI2->CR1 |= 0X08; //BAUD RATE

	SPI2->CR1 |= (1<<2); //MASTER EN
	SPI2->CR1 |= (1<<6); //SPI EN

	//SPI2->CR1 |= (1<<11);      //16bit data frame format enable
}

void SPI2_MOSI(uint8_t b)  //BYTE WRITE TRANMIT
{
	while(!(SPI2->SR & SPI_SR_TXE));   //TRANSMIT BUFFER EMPTY
	SPI2->DR = b;    //STORE A DATA

	while(!(SPI2->SR & SPI_SR_TXE));  //PI hardware copies data from DR → Shift register DR is free You may write next byte

	while(SPI2->SR & SPI_SR_BSY);   //“Wait until SPI has finished sending bits on the wire.”

}
void PAGE_STRING(char *ptr)
{
	while(*ptr != '\0')
		{
			SPI2_MOSI(*ptr);
			ptr++;
		}
}
void PAGE_WRITE()
{

	int i;
	GPIOB->ODR |= (1<<9);//SS=1
	for(i=0;i<1000;i++);
    GPIOB->ODR &= ~(1<<9);//SS=0

    SPI2_MOSI(0X06UL);            //write enable

    GPIOB->ODR |= (1<<9);//SS=1
    for(i=0;i<1000;i++);
    GPIOB->ODR &= ~(1<<9);//SS=0

	SPI2_MOSI(0X02UL);           //write command
	SPI2_MOSI(0X00UL);           //address 16bit so  msb 8 bit
	SPI2_MOSI(0X38UL);           //lsb 8 bit

	PAGE_STRING("embedded");


    GPIOB->ODR |= (1<<9);//SS=1
    for(i=0;i<1000;i++);
    GPIOB->ODR &= ~(1<<9);//SS=0

//	SPI2_MOSI(0X04UL);          //write disable
	///GPIOB->ODR |= (1<<9);//SS=1

}














