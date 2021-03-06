/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : Main program body for led light toggel
 ******************************************************************************
 */


// Port/Pin  : pins are grouped in to port - each pin in port is addressed by pin number
// Pin are accessed by Port+pin number

/* LED 3 - PORT: G
		 - PIN : 13 */
#include <stdint.h>
#define PERIPH_BASE 			(0x40000000UL)
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE 		(PERIPH_BASE + AHB1PERIPH_OFFSET)   // 0x40000000UL + 0x00020000 // peripheral base + offset
#define GPIOG_OFFSET			(0x1800UL) // or 0x1800UL , deleting 0 from front doesn't change the value of the number

#define GPIOG_BASE  			(AHB1PERIPH_BASE + GPIOG_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE 				(AHB1PERIPH_BASE + RCC_OFFSET)

//#define AHB1EN_R_OFFSET 		(0x30UL)
//#define RCC_AHB1EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))
//
//#define MODE_R_OFFSET 			(0x00UL)
//#define GPIOG_MODE_R			(*(volatile unsigned int *)(GPIOG_BASE + MODE_R_OFFSET))
//
//#define OD_R_OFFSET 			(0x14UL)
//#define GPIOG_OD_R 				(*(volatile unsigned int *)(GPIOG_BASE + OD_R_OFFSET))

#define GPIOGEN 				(1U<<6) // ENABLE GPIOG

#define PIN13					(1U<<13) //Set PIN13 HIGH
#define PIN14					(1U<<14)
#define LED_PIN13 				PIN13
#define LED_PIN14 				PIN14
#define __IO 					volatile

typedef struct
{
	__IO uint32_t MODER; 		/* GPIOP port mode register, 						Address offset : 0x00 	*/
	__IO uint32_t OTYPER; 		/* GPIOP port output type register, 				Address offset : 0x04 	*/
	__IO uint32_t OSPEEDR; 		/* GPIOP port output speed register, 				Address offset : 0x08 	*/
	__IO uint32_t PUPDR; 		/* GPIOP port pull-up/pull-down register, 			Address offset : 0x0C 	*/
	__IO uint32_t IDR; 			/* GPIOP port input data register, 					Address offset : 0x010 	*/
	__IO uint32_t ODR; 			/* GPIOP port output data register, 				Address offset : 0x014 	*/
//	__IO uint32_t BSRR; 		/* GPIOP port bit set/reset register, 				Address offset : 0x018 	*/
//	__IO uint32_t LCKR; 		/* GPIOP port configuration lock register, 			Address offset : 0x01C 	*/
//	__IO uint32_t AFR[2] ; 		/* GPIOP alternate function register, 				Address offset : 0x020 	*/
//	//__IO uint32_t AFRH; 		/* GPIOP alternate function high register, 			Address offset : 0x024 	*/
}GPIO_TypeDefM;


typedef struct
{
	volatile uint32_t MODER; 			/* GPIOP port mode register, 						Address offset : 0x00 	*/
	volatile uint32_t DUMMY[4]; 		/* Represents other registers not going to be used for now4 				*/
	volatile uint32_t ODR; 				/* GPIOP port output data register, 				Address offset : 0x014 	*/
}GPIO_TypeDef;

typedef struct
{
	volatile uint32_t DUMMY[12]; 	/* Represents other registers not going to be used for now */
	volatile uint32_t AHB1ENR; 		/*	RCC AHB1 Peripheral clock register, Address offset: 0x14 	*/
}RCC_TypeDef;

#define RCC 					((RCC_TypeDef*) RCC_BASE) 	/* Typecast RCC register to RCC  struct 	*/
#define GPIOG   				((GPIO_TypeDef*)GPIOG_BASE)	/* Typecast GPIOG register to GPIO  struct 	*/
/*
 * (1U<<10) 			//set bit 0 to one
 * &=~(1U<<11) 			//set bit 11 to 0 */

int main(void)
{

	/*1. Enable clock access GPIOG*/

	RCC->AHB1ENR |= GPIOGEN;


	/*2. Set PG5 as output PIN*/



	GPIOG->MODER |= (1U<<26);
	GPIOG->MODER &= ~(1u<<27);

	GPIOG->MODER |= (1U<<28);
	GPIOG->MODER &= ~(1u<<29);

	while(1)
	{
		/* Set PG13, PG14 HIGH */

	//	GPIOG->MODER |= LED_PIN13;
	//	GPIOG->MODER |= LED_PIN14;

		/*4 : Toggle PIN13 */

		GPIOG->ODR ^=LED_PIN14;

		for (int i=0 ; i< 150000; i++)
		{
		}


}


}
