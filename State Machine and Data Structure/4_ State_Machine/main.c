/*
		Name: Abdi Tujuba
		File: main.c
		Development - Board: STM32F446RE
		Description: UART Driver 
*/


#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include "uart.h"
#include <stdint.h>

void SysTick_Handler(void);

#define MAX_STATE      6
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
																			STATE_A_FUNCTION,
																			STATE_B_FUNCTION,
																			STATE_A_FUNCTION,
																			STATE_C_FUNCTION,
																			STATE_B_FUNCTION,
};
static uint16_t  CURRENT_STATE=0;
static int Clock;

int main(void)
{
	HAL_Init(); 
	USART2_Init();
	state_machine_init();	
	//test_setup(); 
	while(1)
	{
		state_table[CURRENT_STATE]();
		HAL_Delay(1000);
		Clock++; 
		
		if(CURRENT_STATE == MAX_STATE)
			CURRENT_STATE = 0; 
	}
	//return 0;
}

void state_machine_init (void){
	CURRENT_STATE=STATE_A; 
	Clock=0; 
}

static uint32_t sa_prev_time=0;
static uint32_t sa_now; 
static double	sa_delta; 

void STATE_A_FUNCTION (void){
	if(Clock % 2)
	{
		CURRENT_STATE++;
		
		sa_now = HAL_GetTick();
		sa_delta= sa_now - sa_prev_time; 
		sa_delta /= 1000; 
		sa_prev_time = sa_now; 
		
		printf("This is the execution of STATE A %f seconds ago\n\r", sa_delta); 
	}
}

static uint32_t sb_prev_time=0;
static uint32_t sb_now; 
static double	sb_delta;

void STATE_B_FUNCTION (void){
		if(Clock % 5)
	{
		CURRENT_STATE++;
		
		sb_now = HAL_GetTick();
		sb_delta= sb_now - sb_prev_time; 
		sb_delta /= 1000; 
		sb_prev_time = sb_now; 
		
		printf("This is the execution of STATE B %f seconds ago\n\r", sb_delta); 
	}
}

static uint32_t sc_prev_time=0;
static uint32_t sc_now; 
static double	sc_delta;

void STATE_C_FUNCTION (void){
	
	if(Clock % 9)
	{
	
		CURRENT_STATE++;
		Clock =0; 
		sc_now = HAL_GetTick();
		sc_delta= sc_now - sc_prev_time; 
		sc_delta /= 1000; 
		sc_prev_time = sc_now;
		
		printf("This is the execution of STATE C %f seconds ago\n\r", sc_delta);
	}
}

void SysTick_Handler(void)
{
	HAL_IncTick();
}
