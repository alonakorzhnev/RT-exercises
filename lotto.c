#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_loto();
void fill_random(int* array, int size);

void print_loto(int* array, int size)
{
	int i, j;
	int col, row, temp;

	char lotto_card[5][11] = {{'0','-', '-','-','-','-','-','-','-','-','-'},
				{'1','-', '-','-','-','-','-','-','-','-','-'},
				{'2','-', '-','-','-','-','-','-','-','-','-'},
				{'3','-', '-','-','-','-','-','-','-','-','-'},
				{'4','-', '-','-','-','-','-','-','-','-','-'}
			};
	
	for(i = 0; i < size; ++i)
	{
		temp = array[i];
		col = temp/10;
		row = temp%10;
		lotto_card[col][row] = '+';
	}

	printf("   ");
	for(j = 1; j <= 10; ++j)
	{
		printf("%d ", j);
	}

	printf("\n");	
	
	for(i = 0; i < 5; ++i)
	{
		for(j = 0; j < 11; ++j)
		{
			printf(" %c", lotto_card[i][j]);
		}
		printf("\n");
	}	
}

void fill_random(int* array, int size)
{
	int i, j, rand_number;
	int flag_random;

	for(i = 0; i < size; ++i)
	{		
		int flag_random = 1;

		while(flag_random)
		{	rand_number = rand()%50 + 1;
			
			for(j = 0; j < size; ++j)
			{
				if(array[j] == rand_number)
				{
					flag_random = 1;
					break;
				}
				else
				{
					flag_random = 0;					
				}

			}						
			
		}
		array[i] = rand_number;
	}
}

int main()
{
	int size = 6;
	int array[6], i;

	srand(time(NULL));

	fill_random(array, size);

	for(i = 0; i < size; ++i)
	{
		printf("%d ", array[i]);
	}

	printf("\n");	
	
	print_loto(array, size);

	return 0;
}
