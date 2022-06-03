 /**
 *	Keil project for I2C 
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 */
#include "stm32f4xx.h"                  // Device header
#include <stdint.h>
 
#define   GPIOBEN 											(1U<<1)
#define   I2C1EN												(1U<<21)
#define 	I2C_100KHZ 										80 // 0b 0101 0000 = Decimal = 80
#define 	SD_MODE_MAX_RISE_TIME					17
#define 	CR1_PE												(1<<0)


#define 	SR2_BUSY											(1U<<1)
#define   CR1_START											(1U<<8)
#define 	SR1_SB												(1U<<0)
#define 	SR1_ADDR											(1U<<1)

#define   SR1_TXE												(1U<<1)
#define 	CR1_ACK												(1U<<7)
#define 	CR1_STOP 											(1U<<9)
#define 	SR1_RXNE 											(1U<<6)
#define 	SR1_BTF												(1U<<2)

 void I2C1_init(void);
 void I2C1_byteRead (char sadd, char maddr, char* data);
 void I2C1_burstRead (char saddr, char maddr, int n, char* data);
 void I2C1_burstWrite (char saddr, char maddr, int n, char* data);
 
 /* PB8 /D15 -------------  SCL
  * PB9 /D14 -------------  SDA
	*/
  void I2C1_init(void)
	{
		/* Enable clock access to GPIOB */
		
		RCC->AHB1ENR |= GPIOBEN;
		
	  /* Set PB8 and PB9 mode to alternet function */ 
		
		GPIOB->MODER &= ~ (1U<<16); 
		GPIOB->MODER |=  (1U<<17);
	
		GPIOB->MODER &= ~ (1U<<18); 
		GPIOB->MODER |=  (1U<<19);		
		
		
		/* Set PB8 and PB9 output type to open drain */
		
		GPIOB->OTYPER |=  (1U<<8); 
		GPIOB->OTYPER |=  (1U<<9);

		/* Enable pullup for PB8 and PB9*/	

	  GPIOB->PUPDR |=  (1U<<16);
  	GPIOB->PUPDR &= ~ (1U<<17); 
		
   	GPIOB->PUPDR |=  (1U<<18);
		GPIOB->PUPDR &= ~ (1U<<19); 
		
		/* Set PB8 and PB9 altenet functyion type to I2C (AF4)*/
		
		//PB8 
		GPIOA->AFR[1]&=~(1U<<0);
		GPIOA->AFR[1]&=~(1U<<1);
		GPIOA->AFR[1]|=(1U<<2);
		GPIOA->AFR[1]&=~(1U<<3);
		
		//PB9 
		GPIOA->AFR[1]&=~(1U<<4);
		GPIOA->AFR[1]&=~(1U<<5);
		GPIOA->AFR[1]|=(1U<<6);
		GPIOA->AFR[1]&=~(1U<<7);

		/* Enable clock access to I2C1*/

		RCC->APB1ENR |= I2C1EN;
		
		/* Enter reset mode */
		I2C1->CR1 |= (1U<<15); 
		
		/* Come out of reset mode */
		I2C1->CR1 &=~ (1U<<15); 
		
		/*Set peripheral clock frequency*/
		
		I2C1->CR2 = (1U<<4); // set frequency to 16 MHz
		
		/* Set I2C to standard mode, 100KHz clock */
		
		I2C1->CCR = I2C_100KHZ; 
		
		/* Set rise Time */
		I2C1->TRISE = SD_MODE_MAX_RISE_TIME; 
		
		/*Enable I2C1*/
		
		I2C1->CR1 |= CR1_PE; 
	}
	
	void I2C1_byteRead (char saddr, char maddr, char* data)
	{
	
		volatile int temp; 
		
		/* wait until bus not busy */
		while ((I2C1->SR2 & SR2_BUSY)){}
			
		/* Generate Start */
			I2C1->CR1|= CR1_START;
			
		/* Wait  until start flag is set */
			while (!(I2C1->SR1 & SR1_SB)){}
				
		/* Transmit slave address + Write */
				
			I2C1->DR = (uint32_t) saddr << 1;
				
		/* wait unitil addr flag is set */
				
		while(!(I2C1->SR1 & (SR1_ADDR))){}

		/* Clear address flag */ 
		
		temp = (int) I2C1->SR2;
					
		/* send memory address */ 
			
		 I2C1->DR = maddr; 
					
	 /* Wait until transmitter empty */
					
			while (!(I2C1->SR1 & SR1_TXE)) {}
					
		/* Generate restart */
				
			I2C1->CR1|= CR1_START;
				
		/* Wait  until start flag is set */
			while (!(I2C1->SR1 & SR1_SB)){}
	
		/* Transmit slave address + Read */	
				
			I2C1->DR = (uint32_t) saddr<<1 | 1; 
				
		/* Wait until addr flag is set */		
		
			while(!(I2C1->SR1 & (SR1_ADDR))) {}
				
		/* Disable Acknowledge */
				
				I2C1->CR1 &= ~CR1_ACK; 
				
		/* clear addr flag */
				
				temp= (int)I2C1->SR2;

		/*Generate stop after data received */	
				
				I2C1->CR1 |= CR1_STOP; 
				
		/*wait until RXNE flag is set */ 
				
				while (!(I2C1->SR1 & SR1_RXNE)){}
					
					*data++= (char)I2C1->DR; 
	}
	
	void I2C1_burstRead (char saddr, char maddr, int n, char* data){
		volatile int temp; 
		
		/* wait until bus not busy */
		while ((I2C1->SR2 & SR2_BUSY)){}
			
		/* Generate Start */
			I2C1->CR1|= CR1_START;
			
		/* Wait  until start flag is set */
			while (!(I2C1->SR1 & SR1_SB)){}
				
		/* Transmit slave address + Write */
				
			I2C1->DR = (uint32_t) saddr << 1;
				
		/* wait unitil addr flag is set */
				
		while(!(I2C1->SR1 & (SR1_ADDR))){}

		/* Clear address flag */ 
		
		temp = (int) I2C1->SR2;
					
		/* send memory address */ 
			
		 I2C1->DR = maddr; 
					
	 /* Wait until transmitter empty */
					
			while (!(I2C1->SR1 & SR1_TXE)) {}
					
		/* Generate restart */
				
			I2C1->CR1|= CR1_START;
				
		/* Wait  until start flag is set */
			while (!(I2C1->SR1 & SR1_SB)){}
	
		/* Transmit slave address + Read */	
				
			I2C1->DR = (uint32_t) saddr<<1 | 1; 
				
		/* Wait until addr flag is set */		
		
			while(!(I2C1->SR1 & (SR1_ADDR))) {}

		/* clear addr flag */
				
				temp= (int)I2C1->SR2;				
				
		/* Disable Acknowledge */
				
				I2C1->CR1 |= CR1_ACK; 
				
		while (n >0)
		{
			/* if one byte */
			
			if(n== 1)
			{
				/* Disable Acknowledge */
				I2C1->CR1 &= ~CR1_ACK; 
				
				/* Generate Stop */
				
				I2C1->CR1 |= CR1_STOP;
				
				/* wait for RXNE flag set */ 
				while(!(I2C1->SR1 & SR1_RXNE)) {}
					/* Read data from DR */
				*data++ = (char) I2C1->DR; 
					
					break; 
			}
			
			else {
				while ((I2C1->SR1 & SR1_RXNE)) {}
					
					/* Read data from DR */ 
					
					(*data++) = (char) I2C1->DR; 
					n--; 
			}
		}
		
	}
	
	
	void I2C1_burstWrite (char saddr, char maddr, int n, char* data){
		volatile int temp;
		
				/* wait until bus not busy */
		while ((I2C1->SR2 & SR2_BUSY)){}
			
		/* Generate Start */
			I2C1->CR1|= CR1_START;
			
		/* Wait  until start flag is set */
			while (!(I2C1->SR1 & SR1_SB)){}
				
		/* Transmit slave address + Write */
				
			I2C1->DR = (uint32_t) saddr << 1;

		/* wait unitil addr flag is set */
				
		while(!(I2C1->SR1 & (SR1_ADDR))){}

		/* Clear address flag */ 
		
		temp = (int) I2C1->SR2;
			
	 /* Wait until data register empty */
					
			while (!(I2C1->SR1 & SR1_TXE)) {}
	
			/* Send memory address */

			I2C1->DR = maddr; 

			for(int i=0; i < n; i++){
			
				/* Wait until data register empty */
				
				while ((I2C1->SR1 & SR1_TXE)) {}
					
					/* Transmit Memory Address */
					I2C1->DR = *data++; 
			}
		
		while(!(I2C1->SR1 & (SR1_BTF))){}		
	}
