				
/*  Set up UART on PIN on 
				PA2 - USART2_TX
				PA3 - USART2_RX
					
*/
#include "stm32f4xx.h"                  // Device header

void usart2_init(void); 
void USART2_write (uint32_t );
char USART2_read(void);

