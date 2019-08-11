#include <stdio.h>
#include "h_string.h"

int main()
{
	int cont = 1, number;		
	unsigned int option;
    	char s1[32], s2[32];
	
	while (cont) {
		printf("Choose option:\n");
		printf("1: Int to bin\n");
		printf("2: Bin to int\n");
		printf("3: Squeeze\n");
		printf("4: Location\n");
		printf("Any another number - stop \n");

		scanf("%x", &option);
		switch (option) {
			case 1:
				printf("Please enter number: ");
				scanf("%d", &number);

				Int2Bin(number, s1);
				
				break;
			
			case 2:
				printf("Please enter string value: ");
				scanf("%s", s1);

				Bin2Int(s1);
				
				break;
			
			case 3:
				printf("Enter first string: ");
				scanf("%s", s1);

				printf("Enter second string: ");
				scanf("%s", s2);

				squeeze(s1, s2);
				
				break;
				
			case 4:
				printf("Enter first string: ");
				scanf("%s", s1);

				printf("Enter second string: ");
				scanf("%s", s2);

				printf("Result: %d\n\n", location(s1, s2));
				
				break;

			default: 
				cont = 0;
				break;
		}
	}

	return 0;
}
