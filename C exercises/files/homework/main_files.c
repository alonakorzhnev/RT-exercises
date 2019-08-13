#include <stdio.h>
#include <stdlib.h>
#include "hw_files.h"

int main()
{
	unsigned int option;
	int cont = 1, result, n = 0;
	char fileName[32];
	
	while(cont)
	{
		printf("Choose option:\n");
		printf("1: Line function\n");
		printf("2: \n");
		printf("3: \n");
		printf("Any another number - stop\n");
		
		scanf("%x", &option);
		switch(option)
		{
			case 1:
				printf("Enter name of file: \n");
				scanf("%s", fileName);
				printf("Enter n lines: \n");
				scanf("%d", &n);
				
				result = last(fileName, n);
				
				break;
				
			case 2:				
				printf("Enter name of file: \n");
				scanf("%s", fileName);
				
				result = countLetters(fileName);
				
				break;
				
			case 3:
				printf("Enter name of file: \n");
				scanf("%s", fileName);
				
				result = countWords(fileName);
				
				break;
				
			default:
				cont = 0;
				break;				
		}
	}
	
	return 0;
}