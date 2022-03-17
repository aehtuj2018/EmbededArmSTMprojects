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

struct ARRAY {
	int32_t data[50]; 
	int32_t capacity; /* Capacity of array is capped at 50 */
	int32_t length;  /* Length of array user want to initialize */ 
}; 

typedef struct ARRAY arrayType; 

void array_append(arrayType *, int32_t ); 
void array_insert(arrayType *, uint32_t , int32_t );
int32_t array_delete(arrayType *arr, uint32_t );
void array_reverse( arrayType *);
int8_t array_isAscending(arrayType *); 
int8_t array_isDescending(arrayType *);
void array_sort_ascend(arrayType *);
void array_sort_descend(arrayType *);
int32_t  array_min(arrayType *);
int32_t  array_max(arrayType *);
int32_t array_sum(arrayType *);
double array_mean(arrayType *);
arrayType array_merge(arrayType *, arrayType *);

int main(void)
{
	USART2_Init();
	
	arrayType signal = {{10,20,30,11,12,13,14,15},50,7};
	arrayType signal_A = {{5,2,3,1,17,13,14,10},50,7};
	arrayType signal_B = {{15,14,11,12,11,10,9},50,7};
	arrayType full_signal;  
	
	printf("\n\r\n\r"); 
	
	printf("The Original array is : \n\r"); 
	
	for (int i=0; i < signal.length; i++)
	{
		printf("  %d", signal.data[i]); 
	}
	printf("\n\r\n\r"); 
	
	array_append(&signal,3000); 
	
	printf("The Appended array is : \n\r");
	
	for (int i=0; i < signal.length; i++)
	{
		printf("  %d", signal.data[i]); 
	}
	
		printf("\n\r\n\r"); 
	
	array_insert(&signal,0, 4000);
	
	printf("Insert an Element at a position: \n\r");
	
	for (int i=0; i < signal.length; i++)
	{
		printf("  %d", signal.data[i]); 
	}
	
	printf("\n\r\n\r"); 
	
	// Delete an Element 
	
	int32_t deleted_element = array_delete(&signal,2); 
	
	printf(" Deleted Element is  %d", deleted_element);
	
	printf("\n\r\n\r"); 
	
	printf("The deleted array is : \n\r");
	
	for (int i=0; i < signal.length; i++)
	{
		printf("  %d", signal.data[i]); 
	}

	printf("\n\r\n\r"); 
	
	// Reverse array
	
	array_reverse(&signal);
	
	printf("The reversed array is : \n\r");
	
	for (int i=0; i < signal.length; i++)
	{
		printf("  %d", signal.data[i]); 
	}
	
	
	// Ascending and Descending 
	
	
	printf("\n\r\n\r"); 
	
	int8_t asc = array_isAscending(&signal_A);
	
	printf("The  array is  Ascending = 1 , Not = 0 result: %d \n\r",asc);
	
	
	printf("\n\r\n\r"); 
	
	int8_t dsc = array_isDescending(&signal_B);
	
	printf("The  array is  Descending = 1 , Not = 0 result: %d \n\r",dsc);
	
	// Sorted Array Ascending 
	
	printf("The  array sorted in Ascending Order is  \n\r");
	
	array_sort_ascend(&signal);
	
	for (int i=0; i < signal.length; i++)
	{
		printf("  %d", signal.data[i]); 
	}
	printf("\n\r\n\r"); 
	// Merge array two array 
	
	printf("The first array \n\r");
	
	
	
	for (int i=0; i < signal.length; i++)
	{
		printf("  %d", signal.data[i]); 
	}
	
	printf("\n\r\n\r"); 
	printf("The Second array \n\r");
	
	for (int i=0; i < signal_A.length; i++)
	{
		printf("  %d", signal_A.data[i]); 
	}
	
	printf("\n\r\n\r"); 
	printf("The Merged  array \n\r");
	
	full_signal = array_merge(&signal,&signal_A);
	
	for (int i=0; i < full_signal.length; i++)
	{
		printf("  %d", full_signal.data[i]); 
	}
	
	printf("\n\r\n\r"); 
	
	return 0; 
}


/******** FUNCTIONS DEFINED ON ARRAY ADT *******/


/* Append or insert at the End  */ 

void array_append(arrayType *arr, int32_t elem)
{
	if(arr->length < arr->capacity)
	{
		arr->data[arr->length++]=elem; // append at the end  
	}
}

/* Insert an Elelemnt  */ 

void array_insert(arrayType *arr, uint32_t idx, int32_t elem)
{
	if((int) idx <= arr->length)
	{
		for(int i=arr->length; i> (int)idx; i--)
		{
		arr->data[i]= arr->data[i-1];  // push array elements from insertion point to the end 
		}
		
	  arr->data[idx]=elem; // insert the required element 
		
		arr->length++; 
		
}
	}

	/* Delete an array element */ 
	
	int32_t array_delete(arrayType *arr, uint32_t idx)
	{

	
		int32_t elem;
		if((int) idx < arr->length )
		{
			elem = arr -> data [idx]; 
		
		
		for(int i = (int) idx; i< arr->length -1 ; i++)
		{
		arr->data[i] = arr->data[i+1]; 		
		}
		arr->length--;
		
		return elem; 
	}
		return 0;
	}
	
	/* Reverse array order */ 
	
	void array_reverse( arrayType *arr)
	{
		int32_t *temp; 
		
		temp = (int32_t *) malloc(arr->length * sizeof(int32_t)); 
		
		for(int i= arr->length -1 , j =0; i>=0; i--, j++)
		{
			temp[j] = arr ->data[i]; 
		}
		
		for(int i=0 ; i< arr->length ; i++)	
		{
			 arr->data[i] = temp [i]; 

		}
		
	}
	
	/* check if array is sorted in Ascending order */ 
	
	int8_t array_isAscending(arrayType *arr)
	{
	  for (int i=0;i<arr->length -1 ; i++)
		{
			if(arr->data[i] > arr->data[i+1]){ 
			return 0; 
			}
		}
 
			return 1; 
	
	}
	
	/* check if array is sorted in Descednding order */ 
	
	int8_t array_isDescending(arrayType *arr)
	{
	  for (int i=0; i < (arr->length - 1); i++)
		{
			if(arr->data[i] < arr->data[i+1])
			return 0; 
		}
 
			return 1; 	
	}
	
	/* Sorting Ascending */
	
	void array_sort_ascend(arrayType *arr){
	
		int32_t i,j,n_temp; 
		
		for(i =1; i< arr->length; i++){
			n_temp = arr->data[i];
			j=i;
			while(j > 0 && n_temp < arr->data[j-1]){
			arr->data[j] = arr->data[j-1];
				j--; 
			}
			arr->data[j] = n_temp; 
			}
		}
	
		/* Sorting Descedning */
		
		void array_sort_descend(arrayType *arr){
	
		int32_t i,j,n_temp; 
		
		for(i =1; i< arr->length; i++){
			n_temp = arr->data[i];
			j=i;
			while(j > 0 && n_temp > arr->data[j-1]){
			arr->data[j] = arr->data[j-1];
				--j; 
			}
			arr->data[j] = n_temp; 
			}
		}
		
		// Find the Maximum Value 
		
		int32_t  array_max(arrayType *arr)
		{
			
			int32_t max = arr->data[0];
			
			for(int i=1; i < arr->length; i++)
			{
				if(arr->data[i] > max)
					max = arr->data[i]; 
			}
			return max; 
		}
		
		// Find the Minimum Value 
		
		int32_t  array_min(arrayType *arr)
		{
			
			int32_t min = arr->data[0];
			
			for(int i=1; i < arr->length; i++)
			{
				if(arr->data[i] < min)
					min = arr->data[i]; 
			}
			return min; 
		}
		
		// Find Sum of the array 
		
		int32_t array_sum(arrayType *arr)
		{
			int32_t sum =0; 
			
			for (int i=0; i < arr->length; i++)
			sum+=arr->data[i]; 
			return sum; 
		}
		
	// Find Average/Mean of the array 
		
		double array_mean(arrayType *arr)
		{
			int32_t sum = 0; 
			double mean = 0;
			
			for (int i=0; i < arr->length; i++)
			sum+=arr->data[i]; 
			
			mean = sum / arr->length ; 
			
			return mean; 
		}
		
		// Merge Array
		
		arrayType array_merge(arrayType *arr1, arrayType *arr2)
		{
			int32_t i =0;
			int32_t j=0; 
			int32_t k=0; 
			
			arrayType *des_array = (arrayType *)malloc(sizeof(arrayType));
			
			/* zipper merge with the smaller member first */
			
			while( i < arr1->length && j < arr2->length){
				if(arr1->data[i] <  arr2->data[j]){
				des_array->data[k++] = arr1-> data[i++]; 
				}
				else {
					des_array->data[k++] = arr2->data[j++]; 
				}
			}
			/* if either one of the array is longer append the remainder of the elements */ 
				
				for(; i< arr1->length; i++){
					des_array->data[k++] = arr1->data[i]; 
				}
				for(;j< arr2->length;j++){
				des_array->data[k++]= arr2->data[j]; 
				}
			des_array->length = arr1->length + arr2->length; 
			
  	return *des_array; 
		}