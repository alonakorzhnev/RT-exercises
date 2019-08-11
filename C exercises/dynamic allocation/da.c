#include <stdio.h>
#include <stdlib.h>
#include "da.h"

int insert(da_str* da, int num)
{
	int* temp;
	
	if(da->index == da->capacity)
	{
		temp = da->arr;
		da->arr = (int*)realloc(da->arr, (da->capacity + 1)*sizeof(int));
		
		if(da->arr == NULL)
		{
			da->arr = temp;
			printf("Error memory allocation\n");
			return -1;
		}
		
		(da->capacity)++;
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
	
	da->arr = (int*)malloc(cap*sizeof(int));
	
	if(da->arr == NULL)
	{
		printf("Error memory allocation\n");
		return NULL;
	}
	
	return da;
}

void print(da_str* da)
{
	int i;
	
	if(da == NULL)
	{
		printf("Null pointer\n");
		return;
	}
	
	printf("Result array: ");
	
	for(i = 0; i < da->index; ++i)
	{
		printf("%d ", da->arr[i]);
	}
	
	printf("\n");
}

void destroy(da_str* da)
{
	free(da->arr);
	free(da);
}