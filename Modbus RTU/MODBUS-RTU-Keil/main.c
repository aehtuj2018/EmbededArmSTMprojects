
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


static  unsigned char MY_SLAVE_ID;

void USART2_IRQHandler(void);

int main (void)
{
	MY_SLAVE_ID=17u;
	unsigned int HoldingRegSize = (sizeof(HoldingRegisters)/sizeof(HoldingRegisters[0])); 
	unsigned int InputRegisterSize = (sizeof(InputRegisters)/sizeof(InputRegisters[0]));
	unsigned int DiscreteInputsSize = (sizeof(DiscreteInputs)/sizeof(DiscreteInputs[0])); 	
	unsigned int CoilsSize = (sizeof(Coils)/sizeof(Coils[0])); 
	
	
	uart2_rxtx_init();
//	USART2->CR1 |= USART2_TXEIE;
//	usart2_init();
	
	while(1)
	{
		
		if((DataPos>=8u) & ((data_in[0]==MY_SLAVE_ID)))
		  {
			DataPos=0;
			//STEP 2: Check function code
			switch(data_in[1])
			{
				case 0x02:
				{
					//checking if requested register count fits in data buffer (256 size - 6)
					//MBProcessRegisters(data_in[1]);
					MBProcessBits(DiscreteInputs,DiscreteInputsSize);
				}
				break;
				case 0x03:
				{
					//checking if requested register count fits in data buffer (256 size - 6)
					//MBProcessRegisters(data_in[1]);
					MBProcessRegisters(HoldingRegisters,HoldingRegSize);
				}
				break;
				case 0x04:
				{
					//checking if requested register count fits in data buffer (256 size - 6)
					//MBProcessRegisters(data_in[1]);
					MBProcessRegisters(InputRegisters,InputRegisterSize);
				}
				break;
				default:
				{
					MBException(0x01); //Illegal function code 01
					MBSendData(ResponseFrameSize);
				}
				break;
			}
		  }
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
	
	/* check if RXNE is set */
	if(USART2->SR & SR_RXNE)
	{	
		
		data_in[DataPos] = (char) USART2->DR;
		DataPos+=1; 

	}
	
}

void TIM6_IRQHandler (void)
{
	/* Clear update interrupt flag */
	TIM6->SR &= ~SR_UIF;

	//Do something 
	
		tim2_callback();	
}

void TIM7_IRQHandler (void)
{
	/* Clear update interrupt flag */
	TIM7->SR &= ~SR_UIF;

	//Do something 
	
		tim2_callback();	
}
