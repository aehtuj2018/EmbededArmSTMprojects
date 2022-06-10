#include "spi.h"

#define SPI1EN      						(1U<<12)
#define GPIOAEN									(1U<<0) 

#define SPI_CR_CPHA       			(1U<<0)
#define SPI_CR_CPOL             (1U<<1)

#define SPI_CR_RXONLY					 ~(1U<<10)
#define SPI_CR_LSBFIRST				 ~(1U<<7)
#define SPI_CR_MASTER					 	(1U<<2)
#define SPI_CR_DFF						 ~(1U<<11)

#define SPI_CR_SSM 							(1U<<9)
#define SPI_CR_SSI							(1U<<8)
#define SPI_CR_SPIEN						(1<<6)

#define SR_TXE 									(1U<<1)
#define SR_RXNE 								(1U<<0)
#define SR_BUSY									(1U<<7)

void spi_gpio_init()
{

	//PA9 - (CS) SPI1_NSS	can use any line , example uses PA9, connected to  CS-MPU
	//PA7 - (SDA) - SPI_MOSI  
	//PA6 - (SDO) - MISO SPI1_MISO 
	//PA5 - (CLK) - SCL
	
	/* Enable clock access  to GPIOA */
		
		RCC->AHB1ENR |= GPIOAEN; 
	
	/* Set PA5, PA6, PA7 mode to alternat function */
	
	/*PA5*/
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |=  (1U<<11);
	
		/*PA6*/
	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER |=  (1U<<13);

		/*PA7*/
	GPIOA->MODER &= ~(1U<<14);
	GPIOA->MODER |=  (1U<<15);

	/*PA9 as output PIN */
	GPIOA->MODER |=  (1U<<18);
	GPIOA->MODER &= ~(1U<<19);


  /* Set PA5, PA6, PA7 alternate function type to SPI1*/
	
	/* PA5 - AFR */
	
	GPIOA->AFR[0] &= ~(1U<<23);
	GPIOA->AFR[0] |=  (1U<<22);
	GPIOA->AFR[0] &= ~(1U<<21);
	GPIOA->AFR[0] |= (1U<<20);
	
	/* PA6 - AFR */
	
	GPIOA->AFR[0] &= ~(1U<<27);
	GPIOA->AFR[0] |=  (1U<<26);
	GPIOA->AFR[0] &= ~(1U<<25);
	GPIOA->AFR[0] |= (1U<<24);

	/* PA7 - AFR */
	
	GPIOA->AFR[0] &= ~(1U<<31);
	GPIOA->AFR[0] |=  (1U<<30);
	GPIOA->AFR[0] &= ~(1U<<29);
	GPIOA->AFR[0] |= (1U<<28);
}

void spi1_config(void)
{
	// Enable clock Access to SPI1
	
	RCC->APB2ENR |= SPI1EN;
	
	/* Set clock to fPCLK/4 */ 
	SPI1->CR1 |=  (1U<<3);
	SPI1->CR1 &= ~(1U<<4);
	SPI1->CR1 &= ~(1U<<5);
	
	
	/* Set CPOL to 1 and CPHA to 1 */
	
	SPI1->CR1 |= SPI_CR_CPHA;
	SPI1->CR1 |= SPI_CR_CPOL;
	
	/* Enable Full Duplex */

		SPI1->CR1 &= SPI_CR_RXONLY; 
	
	/* MSB First - set MSB first*/
	SPI1->CR1 &= SPI_CR_LSBFIRST;
	
	/* Master Configuration -set MAster */
	
	SPI1->CR1 |= SPI_CR_MASTER; 
	
	/* Data Frame Format  - 8 bit*/ 
	
	SPI1->CR1 &= SPI_CR_DFF; 
	
	/* SSM - Select software slave management 
	 * setting SSM=1 and SSI=1 
	*/ 
	
	SPI1->CR1 |= SPI_CR_SSM; 
	SPI1->CR1 |= SPI_CR_SSI; 
	
	/* SPI Enable */
	
	SPI1->CR1 |= SPI_CR_SPIEN; 
	
}

void spi1_transmit(uint8_t *data, uint32_t size)
{
	
	uint32_t i=0;
	uint8_t temp;
	
	while (i< size)
	{
		/* wait unitil TXE is set, wait until buffer empty*/
		while(!(SPI1->SR & (SR_TXE)))
		{}
			
		/* Write the data to be the data register */
		
			SPI1->DR = data[i];			
			i++;						
	}
	/* wait until TXE is Set, wait until buffer empty */
	while(!(SPI1->SR & (SR_TXE))) {}
		
	while(SPI1->SR & (SR_BUSY)) {}
		
	/* Clear overrun flag */
		
		temp = (uint8_t)SPI1->DR; 
		temp = (uint8_t)SPI1->SR; 
		
}


void spi1_receive (uint8_t *data, uint8_t size)
{
	while(size)
	{
		/* send dummy data*/
		
		SPI1->DR = 0; 
	
		/* wait for RXNE flag to be set */		
		while(!(SPI1->SR & (SR_RXNE)))
		{}
		/* Read Data from data register */

					*data++ = (SPI1->DR); 
			size--; 	
	}

}	

void cs_enable(void)
{
	GPIOA-> ODR &= ~(1U<<9); 
}

/* Pull high to disable*/

void cs_disable(void)
{
	GPIOA-> ODR |= (1U<<9); 
}
