/*
		Name: Abdi Tujuba
		File: main.c
		Development - Board: STM32F446RE
		Description: Array - Emebedded Example 
*/

#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include "uart.h"
#include <stdint.h>
#include <stdlib.h>


struct shape {
				uint8_t type;
				int32_t x_coord;
				int32_t y_coord; 
};

typedef struct shape shapeType;

/* 1 = Rectangle 
	 2 = Square 
	 3 = Circle 
	 4 = triangle
*/

int main(void)
{
	USART2_Init();
	
	/* Type 1 Initialization */
	
	shapeType button = {1,5,-2};
	
	printf("The button Type is %d \r\n", button.type); 
	printf("The button cord is (x,y) = (%d,%d)",button.x_coord,button.y_coord); 

	
	/* Type 2 Initialization */ 
	button.type = 2;
	button.x_coord = 10;
	button.y_coord = 12; 

	printf("\r\nThe button Type is %d \r\n", button.type); 
	printf("The button cord is (x,y) = (%d,%d)",button.x_coord,button.y_coord); 
	
	shapeType panel; 
	
	shapeType *pnl; 
	pnl= &panel;
	
	pnl->type = 4;
	pnl->x_coord = -35;
	pnl->y_coord = -70; 
	
	printf("\r\nThe Panel Type is %d \r\n", panel.type); 
	printf("The button cord is (x,y) = (%d,%d)",panel.x_coord,panel.y_coord); 
	
	printf("\r\nThe Panel Type is %d \r\n", (pnl->type)); 
	printf("The button cord is (x,y) = (%d,%d)",(pnl->x_coord),(pnl->y_coord)); 

	/* Dynamic memory Allocation - structure  */
			shapeType *sq;
			sq = (shapeType *)malloc(sizeof(shapeType));

			sq->type = 1;
			sq->x_coord = -500;
			sq->y_coord = -500; 
			
	printf("\r\nThe Panel Type is %d \r\n", (sq->type)); 
	printf("The button cord is (x,y) = (%d,%d)",(sq->x_coord),(sq->y_coord));
	
	while(1)
	{}
	
	//return 0; 
}

