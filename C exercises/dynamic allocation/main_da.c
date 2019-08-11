#include <stdio.h>
#include <stdlib.h>
#include "da.h"

int main()
{	
	int num, capacity, flag_success;
	da_str* da;

	printf("Enter capacity: ");
	scanf("%d", &capacity);

	da = createArray(capacity);
	
	if(da == NULL)
	{
		return -1;
	}

	while(1)
	{
		printf("Enter number: ");
		scanf("%d", &num);
		
		if(num == -1)
		{
			break;
		}	
		
		flag_success = insert(da, num);

		if(flag_success == -1)
		{
			printf("Insert error");
			break;
		}
	}
	
	print(da);
	
	destroy(da);

	return 0;
}
