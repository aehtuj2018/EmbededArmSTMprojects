/*
		Name: Abdi Tujuba
		File: main.c
		Development - Board: STM32F446RE
		Description: Array - Emebedded Example 
*/

#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include "uart.h"
#include <stdint.h>

uint32_t x;
uint32_t *ptr;
uint32_t data[5]; 

int main(void)
{
	USART2_Init();
	
	while(1)
	{
		
		data[0]	= 0xBABEFACE;
		data[1]	= 0xBABADADA;
		data[2]	= 0xDEADBEEF;
		data[3]	= 0xBEEFCAFE;
		
		/* Same: : Set x to the 1st element */ 
		x = data[0];
		x = *data; 
		
		/* Same: : Set ptr to the address of the array*/ 
		
		ptr =  data; 
		printf("this is ptr address %lu\n\r",ptr); 
		ptr = &data[0]; 
		
		/* Same : Set x to the 4th element*/
 		x = data[3];
		x = *(data + 3); 
		
		/* Same : Set ptr to the address of the 4th element */ 
		ptr = data + 3; 
		printf("this is ptr + 3 address %lu\n\r",ptr); 
		ptr = &data[3];

		/* Set the 3rd element of the array to 0x12345678*/
		
		ptr = data;
		data[2] = 0x12345678;
		ptr[2] = 0x12345678; 
		*(ptr + 2 ) = 0x12345678; 
	}
	
	return 0; 
}
