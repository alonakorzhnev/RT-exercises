#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"

int main()
{	
	unsigned int option;
	int cont = 1, capacity;
	Calendar_t* calendar;	
	Meeting_t* meeting;
	int flag_success;
	float begin, end;
	int room;
	
	printf("Enter capacity: ");
	scanf("%d", &capacity);

	calendar = createAD(capacity);
	
	if(calendar == NULL)
	{
		return 0;
	}
	
	flag_success = loadFromFile(calendar);
	
	if(flag_success == 0)
	{
		printf("File successfully loaded.\n\n");
	}
	else if(flag_success == -1)
	{
		printf("File loading failed.\n\n");
		free(calendar);
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
				while(1)
				{		
					printf("Enter begin time: ");
					scanf("%f", &begin);
					printf("Enter eng time: ");
					scanf("%f", &end);
					printf("Enter room number: ");
					scanf("%d", &room);

					if(begin > 0 && begin < 24 && end > 0 && end < 24 && begin < end && room > 0)
					{
						break;
					}

					printf("\nError! Please reenter meeting data.\n");
				}			
				
				meeting = createMeeting(begin, end, room);
				
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
					printf("\nMeeting successfully inserted.\n\n");
				}
				else
				{
					printf("\nMeeting insertion failed.\n\n");
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
	
	flag_success = saveInFile(calendar);
	
	if(flag_success == 0)
	{
		printf("\nData successfully saved.\n");
	}
	else
	{
		printf("\nData saving failed.\n");
	}
	
	destroyAD(calendar);
	
	return 0;
}
