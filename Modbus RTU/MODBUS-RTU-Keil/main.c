
/*----------------------------------------------------------------------------
 * Name:    main.c
 * Purpose: Main usage for STM32
 * Version: V1.00
 *----------------------------------------------------------------------------*/

#include "stm32f4xx.h"                  // Device header
#include "uart.h"
#include "stdio.h"
#include "mbprocess.h"
#include "timer.h"


//unsigned char MY_SLAVE_ID;
extern volatile unsigned TotalCharReceived;

void USART2_IRQHandler(void);
void TIM6_IRQHandler (void);
void TIM7_IRQHandler (void);
	
int main (void)
{
	tim_6_7_1mhz_init();
	//uart2_rxtx_init();
//	USART2->CR1 |= USART2_TXEIE;
 	usart2_init();	
	while(1)
	{
	__NOP(); 
	}
	
// return 0;
}

void USART2_IRQHandler()
{	
	
	/* Disable Timer 6 and 7*/
	TIM6->CR1 &= ~ CR1_CEN; 
	TIM7->CR1 &= ~ CR1_CEN;
	
	/* clear counter values */
	TIM6->CNT = 0;
	TIM7->CNT = 0; 
	
	if(DataPos >= 256)
	{
		DataPos=0;
	}
	else 
	{	 
		/* check if RXNE is set */
		if(USART2->SR & SR_RXNE)
		{	
			data_in[DataPos] = (char) USART2->DR;
			DataPos+=1;		
			TotalCharReceived = DataPos;
		}		
	}	
}

void TIM6_IRQHandler (void)
{
	if(TIM6->SR == 1U) // check if interrupt is set 		
	{
		TIM6->CR1 &= ~CR1_CEN;  // Stop 1.5 Character Timer 
		TIM6->CNT = 0;					// Clear Counter 
		DataPos=0; 							// Clear the index and start over 
    TIM6->SR &= ~SR_UIF;	 // Clear update interrupt flag 
	}
	
	//Do something 
	
		//tim2_callback();	
}

void TIM7_IRQHandler (void)
{
	if(TIM7->SR == 1U) // check if interrupt is set 		
	{
		TIM7->CR1 &= ~CR1_CEN;  // Stop 1.5 Character Timer 
		TIM7->CNT = 0;					// Clear Counter 
		DataPos=0; 							// Clear the index and start over 
		TIM7->SR &= ~SR_UIF;	 // Clear update interrupt flag 
		CheckMBPDU();
    
	}
	
}
