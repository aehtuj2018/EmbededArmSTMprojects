/*
		Name: Abdi Tujuba
		File: main.c
		Development - Board: STM32F446RE
		Description: UART Driver 
*/


#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include "uart.h"

enum states{
	STATE_A  = 0,
	STATE_B, 
	STATE_C
};

typedef enum  states STATE_TYPE; 

void STATE_A_FUNCTION (void);
void STATE_B_FUNCTION (void); 
void STATE_C_FUNCTION (void);
void state_machine_init (void);

static void (*state_table[])(void)= { STATE_A_FUNCTION,
																			STATE_B_FUNCTION,
																			STATE_C_FUNCTION
};
static STATE_TYPE CURRENT_STATE;
static int Clock;

int main(void)
{
	USART2_Init(); 
	//test_setup(); 
	while(1)
	{
		state_table[CURRENT_STATE]();
		Clock++; 
	}
	return 0;
}

void state_machine_init (void){
	CURRENT_STATE=STATE_A; 
	Clock=0; 
}

void STATE_A_FUNCTION (void){
	if(Clock == 2)
	{
		CURRENT_STATE=STATE_B;
		printf("This is the execution of STATE A \n\r"); 
	}
}
void STATE_B_FUNCTION (void){
		if(Clock == 5)
	{
		CURRENT_STATE=STATE_C;
		printf("This is the execution of STATE B \n\r"); 
	}
}
void STATE_C_FUNCTION (void){
	
	if(Clock == 9)
	{
		Clock = 0; 
		CURRENT_STATE=STATE_A;
		printf("This is the execution of STATE C \n\r"); 
	}
}