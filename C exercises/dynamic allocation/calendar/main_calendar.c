#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"

int main()
{	
	unsigned int option;
	int cont = 1, capacity;
	Calendar_t* calendar;
	
	Meeting_t* meeting;
	int flag_success = 0;
	
	printf("Enter capacity: ");
	scanf("%d", &capacity);

	calendar = createAD(capacity);
	
	if(calendar == NULL)
	{
		return 0;
	}
	
	while(cont)
	{
		printf("Choose option:\n");
		printf("1: Insert meeting\n");
		printf("2: Remove meeting\n");
		printf("3: Find meeting\n");
		printf("4: Print calendar\n");
		printf("Any another number - stop\n");
		
		scanf("%x", &option);
		switch(option)
		{
			case 1:				
				meeting = createMeeting();
				
				flag_success = insertMeeting(calendar, meeting);
				
				break;
			
			case 2:
				
				break;
				
			case 3:
				
				break;
				
			case 4:
				printAD(calendar);
				
				break;
				
			default:
				cont = 0;
				break;
		}
	}
	

	return 0;
}
