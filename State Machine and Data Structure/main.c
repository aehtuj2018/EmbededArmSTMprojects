/*
		Name: Abdi Tujuba
		File: main.c
		Development - Board: STM32F446RE
		Description: UART Driver 
*/


#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include "uart.h"
int main(void)
{
	USART2_Init(); 
	test_setup(); 
	while(1)
	{
	}
	return 0;
}