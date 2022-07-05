
/*----------------------------------------------------------------------------
 * Name:    main.c
 * Purpose: Main usage for STM32
 * Version: V1.00
 *----------------------------------------------------------------------------*/

#include "stm32f4xx.h"                  // Device header
#include "uart.h"
#include "stdio.h"
#include "mbprocess.h"

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
	/* check if RXNE is set */
	
	if(USART2->SR & SR_RXNE)
	{	
		
		data_in[DataPos] = (char) USART2->DR;
		DataPos+=1; 
		/* Read data*/ 
		//uart_callback();
	}
	
 //check if we are here because of TXEIE interrupt
 /*if (USART1->SR & USART_SR_TXE) //if RX is not empty
 {
  //handle transmit completion here
 }*/
	
}

/*static void uart_callback()
{
	data = (char) USART2->DR;
	
	printf("char is %c\r\n",data); 
	
}*/
