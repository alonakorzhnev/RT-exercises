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

	int i, *begin = &array[0], *end = &array[size -1];	
	
	while(begin < end)
	{

		while(*begin == 0)
		{
			begin++;
		}
		while(*end == 1)
		{
			end--;
		}
		if(begin < end)
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
