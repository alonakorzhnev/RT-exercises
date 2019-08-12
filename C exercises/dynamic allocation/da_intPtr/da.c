#include <stdio.h>
#include <stdlib.h>
#include "da.h"

int insert(da_str* da, intPtr num)
{
	intPtr* temp;
	
	if(da == NULL)
	{
		printf("Null pointer\n");
		return -1;
	}
	
	if(da->index == da->capacity)
	{
		temp = da->arr;
		da->arr = (intPtr*)realloc(da->arr, (da->capacity*2)*sizeof(intPtr));
		
		if(da->arr == NULL)
		{
			da->arr = temp;
			printf("Error memory allocation\n");
			return -1;
		}
		
		printf("Memory allocation\n");
		(da->capacity) *= 2;
	}

	da->arr[da->index] = num;
	(da->index)++;
	
	return 0;
}

da_str* createArray(int cap)
{
	da_str* da;
	da = (da_str*)malloc(sizeof(da_str));
	
	if(da == NULL)
	{
		printf("Error memory allocation\n");
		return NULL;
	}
	
	da->capacity = cap;
	da->index = 0;
	
	da->arr = (intPtr*)malloc(cap*sizeof(intPtr));
	
	if(da->arr == NULL)
	{
		printf("Error memory allocation\n");
		free(da);
		return NULL;
	}
	
	return da;
}

void print(da_str* da)
{
	int i;
	
	if(da == NULL || da->arr == NULL)
	{
		printf("Null pointer\n");
		return;
	}
	
	printf("Result array: ");
	
	for(i = 0; i < da->index; ++i)
	{
		if(da->arr[i] == NULL)
		{
			printf("Null pointer\n");
			return;
		}
		
		printf("%d ", *(da->arr[i]));
	}
	
	printf("\n");
}

void destroy(da_str* da)
{
	int i;
	
	if(da == NULL || da->arr == NULL)
	{
		printf("Null pointer\n");
		return;
	}
	
	for(i = 0; i < da->index; ++i)
	{
		free(da->arr[i]);
	}
	
	free(da->arr);
	free(da);
}