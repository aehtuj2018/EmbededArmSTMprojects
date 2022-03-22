
/**
 *	Keil project for UART_TX 
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 */

#ifndef UART_H_
#define UART_H_


#include <stdint.h>

#include "stm32f4xx.h"
//void uart2_tx_init(void); 
void uart2_rxtx_init(void);
char uart2_read(void);
void uart2_write(int ch);
void uart2_rx_interrupt_init(void);
void uart2_tx_init(void);
void dma1_stream6_init(uint32_t , uint32_t , uint32_t );

#define SR_RXNE 							(1U<<5)
#define HISR_TCIF6					  (1U<<21)
#define HIFCR_CTCIF6					(1U<<21)

#endif /* UART_H_ */
