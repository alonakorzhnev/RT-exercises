#include <stdio.h>
#include "bitMap.h"

int main() 
{
	unsigned int option;
	int cont = 1, nf, result, num;
	BitMap* bm;
	bitFunc func[3] = {bitOn, bitOff, bitStatus};
	
	printf("Enter number of fitchers: ");
	scanf("%d", &nf);
	
	bm = createBM(nf);
	
	if(bm == NULL)
	{
		return 0;
	}
	
	while(cont)
	{
		printf("Choose option: \n");
		printf("1: Bit on: \n");
		printf("2: Bit off: \n");
		printf("3: Bit status: \n");
		printf("4: Print bit map: \n");
		printf("Any another number - stop\n");
		
		scanf("%x", &option);
		switch(option)
		{
			case 1:
				printf("Enter number of bit to on: \n");
				scanf("%d", &num);
				
				result = callFunc(func[0], bm, num);
				
				if(result == -1)
				{
					printf("\nError in function bitOn\n\n");
				}
				
				break;
				
			case 2:
				printf("Enter number of bit to off: \n");
				scanf("%d", &num);
				
				result = callFunc(func[1], bm, num);
				
				if(result == -1)
				{
					printf("\nError in function bitOff\n\n");
				}
				
				break;
				
			case 3:
				printf("Enter number of bit to check status: \n");
				scanf("%d", &num);
				
				result = result = callFunc(func[2], bm, num);
				
				if(result == -1)
				{
					printf("\nError in function bitStatus\n\n");
				}
				else
				{
					printf("\nBit status: %d\n\n", result);
				}
				
				break;
				
			case 4:
				
				result = printBM(bm);
				
				if(result == -1)
				{
					printf("\nError in function printBM\n\n");
				}
				
				break;
				
			default:
				cont = 0;
				break;				
		}
	}
	
	destroyBM(bm);
	
	return 0;
}