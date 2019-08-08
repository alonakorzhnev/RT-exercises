#include <stdio.h>

void occur_value(int* array, int size);
void swap(int* x, int* y);

void swap(int* x, int* y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void occur_value(int* array, int size)
{
	int max_count = 0, count = 0, first_index = 0;
	int i, j;

	for(i = 0; i < size; ++i) 
	{
		count = 0;
		
		for(j = 0; j < size; ++j) 
		{
			if (array[i] == array[j])
			{
		     		++count;
			}
		}

		if(count > max_count)
		{
			max_count = count;
			first_index = i;
		}
 	}

	printf("%d\n", array[first_index]);
	
}

int main()
{
	int size = 8, i;
	int array[8];
	printf("Please enter numbers(8): ");

	for(i = 0; i < size; ++i)
	{
		scanf("%d", &array[i]);
	}

	occur_value(array, size);

	return 0;
}
