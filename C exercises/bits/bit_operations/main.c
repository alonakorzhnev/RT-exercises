#include <stdio.h>
#include "bitOp.h"

int main() 
{
	unsigned int option;
	int cont = 1;
	int n, p, steps, x, y;
	unsigned char result;
	
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
				
				printf("N: ");
				char2Bin(n);
				result = bitInvers(n);
				printf("Result: ");
				char2Bin(result);
				
				break;
				
			case 2:
				printf("Enter number and steps to rotate: ");
				scanf("%d%d", &n, &steps);
				
				printf("N: ");
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
				result = setBits1(x, p, n, y);				
				printf("Result: ");
				char2Bin(result);
								
				break;
				
			case 4:
				
				break;
				
			default:
				cont = 0;
				break;				
		}
	}
		
	return 0;
}