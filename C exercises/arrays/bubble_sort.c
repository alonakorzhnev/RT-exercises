#include <stdio.h>

void bubble_sort(int* array, int size);
void swap(int* x, int* y);

void swap(int* x, int* y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void bubble_sort(int* array, int size)
{
	int i, j;	
	
	for(i = 0; i < size - 1; ++i)
	{
		for(j = 0; j < size - 1 - i; ++j)
		{
			if(array[j] > array[j + 1])
			{
				swap(&array[j], &array[j + 1]);
			}
		}
		
	}
	
}

int main()
{
	int size = 6, i;
	int array[6];

	printf("Please enter numbers(6): ");

	for(i = 0; i < size; ++i)
	{
		scanf("%d", &array[i]);
	}

	bubble_sort(array, size);
	
	for(i = 0; i < size; ++i)
	{
		printf("%d ", array[i]);
	}

	printf("\n");

	return 0;
}
