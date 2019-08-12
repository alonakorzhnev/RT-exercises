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
				
				if(meeting == NULL)
				{
					break;
				}
				else
				{
					printf("\nNew meeting has been created.\n\n");
				}
				
				flag_success = insertMeeting(calendar, meeting);
				
				if(flag_success == 0)
				{
					printf("Meeting successfully inserted.\n\n");
				}
				else
				{
					printf("Meeting insertion failed.\n\n");
				}
				
				break;
			
			case 2:
				flag_success = removeMeeting(calendar);
				
				if(flag_success == 0)
				{
					printf("\nMeeting successfully removed.\n\n");
				}
				else
				{
					printf("\nThere is no such meeting.\n\n");
				}
				
				break;
				
			case 3:
				meeting = findMeeting(calendar);
				
				if(meeting != NULL)
				{
					printf("\nMeeting is found.\n");
					printMeeting(meeting);
					printf("\n");
				}
				else
				{
					printf("\nMeeting is not found.\n\n");
				}
				
				break;
				
			case 4:
				printAD(calendar);				
				break;
				
			default:
				cont = 0;
				break;
		}
	}
	
	destroyAD(calendar);
	
	return 0;
}
