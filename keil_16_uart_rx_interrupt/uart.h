
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

#define SR_RXNE 							(1U<<5)
#include <stdint.h>

#include "stm32f4xx.h"
//void uart2_tx_init(void); 
void uart2_rxtx_init(void);
char uart2_read(void);
void uart2_write(int ch);
void uart2_rx_interrupt_init(void);

#endif /* UART_H_ */
