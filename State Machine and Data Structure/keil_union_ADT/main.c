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
				int32_t y_cord;
};

typedef struct shape shapeType;

union COORD2{
	 int8_t x;
	 int8_t y; 
};

struct screen  {
		shapeType shapes[2];
		uint32_t height;
		uint32_t width; 
};


typedef struct screen screenType;

typedef union  COORD2 coord2Type;

/* 1 = Rectangle 
	 2 = Square 
	 3 = Circle 
	 4 = triangle
*/


int main(void)
{
	USART2_Init();

		shapeType shapes[5]={{0,-3,-5},
												 {1,7,7},
												 {2,5,0},
												 {1,8,-2},
												 {3,4,4}
												};  //coord1Type location1 = {-3,4};
												
		screenType homescreen;
		homescreen.shapes[0].type = 1; 
		homescreen.shapes[0].x_coord = -10;
		homescreen.shapes[0].y_cord = -10;
		homescreen.height = 20;
		homescreen.width = 20; 

												
		coord2Type location2 = {5};
	
		location2.x = 6; 
		location2.y = 45; 
		
		for(int i=0; i < (sizeof(shapes)/sizeof(shapes[0])); i++)
		{
		printf("The Shapes are Shape Type: %d, x-coordinate : %d , y-coordinate %d",shapes[i].type, shapes[i].x_coord, shapes[i].y_cord); 
		printf("\r\n"); 
		}
//	/* Type 1 Initialization */
//	
//	shapeType button = {1,5,-2};
//	
//	printf("The button Type is %d \r\n", button.type); 
//  	printf("The Coordinates for Location 1 are (x,y) = (%d,%d)",location1.x,location1.y); 

//	
//	/* Type 2 Initialization */ 
//	button.type = 2;
//	button.x_coord = 10;
//	button.y_coord = 12; 

		
//		printf("The Cordinates for location 2 are (x,y) = (%d,%d)",location2.x,location2.y); 
//	
//	shapeType panel; 
//	
//	shapeType *pnl; 
//	pnl= &panel;
//	
//	pnl->type = 4;
//	pnl->x_coord = -35;
//	pnl->y_coord = -70; 
//	
//	printf("\r\nThe Panel Type is %d \r\n", panel.type); 
//	printf("The button cord is (x,y) = (%d,%d)",panel.x_coord,panel.y_coord); 
//	
//	printf("\r\nThe Panel Type is %d \r\n", (pnl->type)); 
//	printf("The button cord is (x,y) = (%d,%d)",(pnl->x_coord),(pnl->y_coord)); 

//	/* Dynamic memory Allocation - structure  */
//			shapeType *sq;
//			sq = (shapeType *)malloc(sizeof(shapeType));

//			sq->type = 1;
//			sq->x_coord = -500;
//			sq->y_coord = -500; 
//			
//	printf("\r\nThe Panel Type is %d \r\n", (sq->type)); 
//	printf("The button cord is (x,y) = (%d,%d)",(sq->x_coord),(sq->y_coord));
//	
	while(1)
	{}
	
	//return 0; 
}

