/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : Main program body for led light toggel
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
// Port/Pin  : pins are grouped in to port - each pin in port is addressed by pin number
// Pin are accessed by Port+pin number

/* LED 3 - PORT: G
		 - PIN : 13 */

#define PERIPH_BASE 			(0x40000000UL)
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE 		(PERIPH_BASE + AHB1PERIPH_OFFSET)   // 0x40000000UL + 0x00020000 // peripheral base + offset
#define GPIOG_OFFSET			(0x00001800UL) // or 0x1800UL , deleting 0 from front doesn't change the value of the number

#define GPIOG_BASE  			(AHB1PERIPH_BASE + GPIOG_OFFSET)

#define RCC_OFFSET				(0x00003800UL)
#define RCC_BASE 				(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET 		(0x30UL)
#define RCC_AHB1EN_R			(RCC_BASE + AHB1EN_R_OFFSET)

#define MODE_R_OFFSET 			(0x00UL)
#define GPIOA_MODE_R			(GPIOG_BASE + MODE_R_OFFSET)

#define 						(1U<<11)

# define GPIOGEN 				(1U<<6) // enable

/*
 * (1U<<10) 			//set bit 0 to one
 * &=~(1U<<11) 			//set bit 11 to 0 */


