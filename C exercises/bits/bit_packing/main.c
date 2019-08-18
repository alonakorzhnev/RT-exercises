#include <stdio.h>
#include "bit_pack.h"

int main() 
{
	unsigned int option;
	int cont = 1, size;
	char* string;
	
	while(cont)
	{
		printf("Choose option: \n");
		printf("1: Without bit field option: \n");
		printf("2: With bit field option: \n");
		printf("Any another number - stop\n");
		
		scanf("%x", &option);
		switch(option)
		{
			case 1:
				printf("Enter string to pack: ");
				scanf("%s", string);
				
				size = withoutBitField(string);
				
				if(size%2 == 0)
				{
					printBits(string, size/2);
				}
				else
				{
					printBits(string, size/2 + 1);
				}				
								
				break;
				
			case 2:
				printf("Enter string to pack: ");
				scanf("%s", string);
				
				size = withBitField(string);
				
				if(size%2 == 0)
				{
					printBits(string, size/2);
				}
				else
				{
					printBits(string, size/2 + 1);
				}
				
				break;
										
			default:
				cont = 0;
				break;				
		}
	}
		
	return 0;
}