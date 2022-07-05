				
/*  Set up UART on PIN on 
				PA2 - USART2_TX
				PA3 - USART2_RX
					
*/
#include "stm32f4xx.h"                  // Device header

void usart2_init(void); 
void USART2_write (uint32_t );
char USART2_read(void);

#define GPIOAEN       		(1U<<0)  //GPIOA enable 
#define UART2EN						(1U<<17) // USART 2 Enable Clock Access 
#define USART2EN 					(1U<<13) // USART Enable
#define USART2_M					(1U<<12) // 1 start bit, 8 Databits n stop bit
#define USART2_PEIE   		(1U<<8) // Interrupt is generated when PE = 1 in Status Register
#define USART2_TXEIE   		(1U<<7) // Interrupt is generated when TXE =1 in Status Reg
#define USART2_TCIE				(1U<<6) // Interrupt is generated when TC=1 in Status Reg/USART_SR
#define USART2_RXNEIE     (1U<<5) // Interrupt is generated whenever ORE=1 or RXNE=1 status Reg
#define USART2_TE					(1U<<3) // Trasmitter Enable 
#define USART2_RE					(1U<<2) // Receiver Enable 
#define UART_BAUD_RATE     115200 // Baud Rate 
#define APB2_CLK           16000000 // clock frequency 

#define USART2_TXE         (1U<<7)
#define USART2_RXNE        (1U<<5)

#define CR1_RXNEIE 				 (1U<<5)


#define SR_RXNE            (1U<<5)