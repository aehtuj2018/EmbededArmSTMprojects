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



uint32_t sig[] = {23, 567, 0, 12, 144, 134, 13, 4};
uint32_t output[4] ; 

void array_2_max(uint32_t *, uint32_t *, uint32_t );

void dsplay_array(uint32_t *, uint32_t );


int main(void)
{
	USART2_Init();
	//dsplay_array(sig,8);
	array_2_max(sig,output,8 ); 

	printf("From main \n\r"); 
	dsplay_array(output,4); 
	
	return 0; 
}

void dsplay_array(uint32_t *src_array, uint32_t src_len)
{
	for(int i = 0; i < src_len; i++)
	printf(" src_array [ %d] =  %d\n\r", i, src_array[i]); 
}


void array_2_max(uint32_t *src_array, uint32_t *dest_array, uint32_t src_len)
{
	 
	uint32_t max1 = 0;
	uint32_t max2 = 0;
	uint32_t max1_idx = 0;
	uint32_t max2_idx = 0;
	
	// dsplay_array(src_array,8);
	
	max1 = src_array[0];
	
	for (int i=0; i < src_len; i++)
	{
		if(src_array[i] >  max1)
		{
			max1=src_array[i];
			max1_idx = i; 
		}
}
	
max2 = src_array[0];

for (int i=0; i < src_len; i++)
{
	/* Skip the largest value */
	
	if(src_array[i] != max1)
	{		
		if(src_array[i] >  max2)
		{
			max2=src_array[i];
			max2_idx = i; 
		}
	}
		
}

dest_array[0] = max1;
dest_array[1] = max1_idx;
dest_array[2] = max2;
dest_array[3] = max2_idx; 
	
printf("Output Array \n\r"); 
	dsplay_array(dest_array,4);
__NOP(); 
}