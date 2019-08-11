#include <stdio.h>
#include <stdlib.h>

int* insert(int num, int* arr, int* index, int* capacity);

int* insert(int num, int* arr, int* index, int* capacity)
{
	int* temp;
	int i;

	if(arr == NULL || index == NULL || capacity == NULL)
	{
		return NULL;
	}

	if(*index == *capacity)
	{
		temp = arr;
		arr = (int*)realloc(arr, (*capacity + 1)*sizeof(int));
		
		if(arr == NULL)
		{
			arr = temp;
			printf("Error memory allocation\n");
			return NULL;
		}
		(*capacity)++;
	}

	arr[*index] = num;

	(*index)++;
	return arr;
}

int main()
{
	int *arr, *temp;
	int num, i;
	int capacity, index = 0;

	printf("Enter capacity: ");
	scanf("%d", &capacity);

	arr = (int*)malloc(capacity*sizeof(int));
	
	if(arr == NULL)
	{
		return -1;
	}

	while(1)
	{
		printf("Enter the number: ");
		scanf("%d", &num);
		
		if(num == -1)
		{
			break;
		}	
		
		temp = arr;
		arr = insert(num, arr, &index, &capacity);

		if(arr == NULL)
		{
			arr = temp;
		}
	}
	
	printf("Result array: ");
	for(i = 0; i < index; ++i)
		printf("%d", arr[i]);

	free(arr);

	return 0;
}
