/*
		Name: Abdi Tujuba
		File: uart.c
		Development - Board: STM32F446RE
		Description: UART Driver 
*/
#include "uart.h"
#include <stdio.h>

void USART2_Init(void);
int USART2_write(int ch);
int USART2_read(void); 
void test_setup(void);

#define APB1EN			(1U<<17)
#define AHB1EN			(1U<<0)

// configure uart

void USART2_Init(void)
{
// 1. Enable clock Access to uart2
	
	//RCC->APB1ENR |= APB1EN;
	RCC->APB1ENR |= 0x20000;
// 2. Enable clock access to portA
	
	//RCC->AHB1ENR |= AHB1EN; 
	RCC->AHB1ENR |= 0x01; 
	
// 3. Enable pins for alternet function PA2, PA3 

		GPIOA->MODER &=~0x00F0; // Disable first 
		GPIOA->MODER |= 0x00A0; // PA2 and PA3
	
	
// 4. Configure type of alternet function => AF7
	
	GPIOA->AFR[0] &= ~0xFF00; //disable 
	GPIOA->AFR[0] |= 0x7700; 

// configure uart, BAUD Rate, STOP bit 
	USART2->BRR = 0x683; // Baud Rate 
	USART2->CR1 = 0x00C; // Data size , enable transfer recive and transmit 
	USART2->CR2 = 0x000; // STOP bit one 
	USART2->CR3 = 0x000; //No flow control
	USART2->CR1 |= 0x2000; // Enable USART 2 
	
}

int USART2_write(int ch)
{
	while(!(USART2->SR & 0x0080)){} // while the transfer buffer is not empty wait 
	USART2->DR= ch&0xFF; 
		
	return ch;
}

int USART2_read(void)
{
	while(!(USART2->SR & 0x0020)){} // while there is no character wait 
	return (int) USART2->DR;
}

/* The code below is the interface to the C standard I/O library.
 * All the I/O are directed to the console.
 */
//struct __FILE {  int handle; };
//FILE __stdin  = {0};
//FILE __stdout = {1};
// = {2};


FILE __stdout;
FILE __stdin;
FILE __stderr;

/* Called by C library console/file output */
int fputc(int ch , FILE * stream)
{
	USART2_write(ch);
	return ch;  //return the character written to denote a successfull write
}


int fgetc(FILE * stream)
{
	
	int c = USART2_read();
	USART2_write(c); //To echo Received characters back to serial Terminal
	return c;
}

	
 int n;

 char str[80];

void test_setup(void){
	
	printf("please enter a number: ");
	scanf("%d", &n);
	printf("the number entered is: %d\r\n", n);
	printf("please type a character string: ");
	gets(str);
	printf("the character string entered is: ");
	puts(str);
	printf("\r\n");
	
}
