#include <stdio.h>

void sort(int* array, int size);

void sort(int* array, int size)
{
	/*int i, count_zero = 0;

	for(i = 0; i < size; ++i)
	{
		if(array[i] == 0)
		{
			++count_zero;
		}
	}	
	
	for(i = 0; i < size; ++i)
	{
		if(i < count_zero)
		{
			array[i] = 0;
		}
		else
		{
			array[i] = 1;
		}
	}*/

	int *begin = array, *end = array + size;
	while(begin < end)
	{

		if(*begin == 0)
		{
			begin++;
		}
		else if(*end == 1)
		{
			end--;
		}
		else
		{
			*begin = 0;
			*end = 1;	
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

	sort(array, size);
	
	for(i = 0; i < size; ++i)
	{
		printf("%d ", array[i]);
	}

	printf("\n");

	return 0;
}
