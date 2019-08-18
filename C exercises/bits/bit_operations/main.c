#include <stdio.h>
#include "bitOp.h"

int main() 
{
	unsigned int option;
	int cont = 1;
	int n, p, steps, x, y, i, j, value;
	unsigned char result;
	unsigned int w, number;
	
	while(cont)
	{
		printf("Choose option: \n");
		printf("1: Bits inversion: \n");
		printf("2: Bits rotation: \n");
		printf("3: Set bits: \n");
		printf("4: Set bits: \n");
		printf("Any another number - stop\n");
		
		scanf("%u", &option);
		switch(option)
		{
			case 1:
				printf("Enter number: ");
				scanf("%d", &n);
				
				printf("Number: ");
				char2Bin(n);
				result = bitInvers(n);
				printf("Result: ");
				char2Bin(result);
				
				break;
				
			case 2:
				printf("Enter number and steps to rotate: ");
				scanf("%d%d", &n, &steps);
				
				printf("Number: ");
				char2Bin(n);
				result = bitRotate(n, steps);
				printf("Result: ");
				char2Bin(result);
				
				break;
				
			case 3:
				printf("Enter x, p, n, y: ");
				scanf("%d%d%d%d", &x, &p, &n, &y);
				
				printf("X: ");
				char2Bin(x);
				printf("Y: ");
				char2Bin(y);
				result = setBitsFirst(x, p, n, y);				
				printf("Result: ");
				char2Bin(result);
								
				break;
				
			case 4:
				
				printf("Enter w, i, j, value: ");
				scanf("%u%d%d%d", &w, &i, &j, &value);
				
				printf("Number: ");
				int2Bin(w);
				number = setBitsSecond(w, i, j, value);		
				
				if(number == 0)
				{
					printf("\nYou have entered the wrong data.");
					break;
				}
				printf("\nResult: ");
				int2Bin(number);
				printf("\n");
				
				break;
				
			default:
				cont = 0;
				break;				
		}
	}
		
	return 0;
}