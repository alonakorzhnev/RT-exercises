#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"

Calendar_t* createAD(int capacity)
{
	Calendar_t* calendar;
	calendar = (Calendar_t*)malloc(sizeof(Calendar_t));
	
	if(calendar == NULL)
	{
		return NULL;
	}
	
	calendar->meetings = (Meeting_t**)malloc(capacity*sizeof(Meeting_t*));
	
	if(calendar->meetings == NULL)
	{
		free(calendar);
		return NULL;
	}
	
	calendar->capacity = capacity;
	calendar->index = 0;
	
	printf("Calendar has been created\n\n");
	return calendar;
}

Meeting_t* createMeeting()
{
	Meeting_t* meeting;
	float begin, end;
	int room;
	
	meeting = (Meeting_t*)malloc(sizeof(Meeting_t));
	
	if(meeting == NULL)
	{
		return NULL;
	}
	
	while(1)
	{
		printf("Please enter meeting data\n");
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
	}
	
	meeting->begin = begin;
	meeting->end = end;
	meeting->room = room;	
	
	printf("New meeting has been created\n\n");
	return meeting;
}

int insertMeeting(Calendar_t* calendar, Meeting_t* meeting)
{
	Meeting_t** temp;
	int i, insert_index = -1;
	
	if(calendar == NULL || meeting == NULL)
	{
		return -1;
	}	
	
	if(calendar->index == 0)
	{
		insert_index = 0;
	}
	else if(meeting->end <= calendar->meetings[0]->begin)
	{		
		insert_index = 0;
	}
	else if(meeting->begin >= calendar->meetings[calendar->index - 1]->end)
	{
		insert_index = calendar->index;		
	}
	else
	{
		for(i = 0; i < calendar->index - 1; ++i)
		{
			if(meeting->begin >= calendar->meetings[i]->end && meeting->end <= calendar->meetings[i + 1]->begin)
			{
				insert_index = i + 1;
			}
		}
	}
	
	if(insert_index == -1)
	{
		printf("Meetings overlap!\n\n");
		free(meeting); /*or in main*/
		return -1;
	}
	
	if(calendar->index == calendar->capacity)
	{
		temp = calendar->meetings;
		calendar->meetings = (Meeting_t**)realloc(calendar->meetings, (calendar->capacity*2)*sizeof(Meeting_t*));
		
		if(calendar->meetings == NULL)
		{
			calendar->meetings = temp;
			free(meeting);
			return -1;
		}
		
		printf("Memory allocation\n\n");
		(calendar->capacity) *= 2;
	}

	if(insert_index != calendar->index)
	{
		for(i = calendar->index; i > insert_index; --i)
		{
			calendar->meetings[i] = calendar->meetings[i - 1];
		}
	}

	calendar->meetings[insert_index] = meeting;
	(calendar->index)++;
	
	return 0;
}

int removeMeeting(Calendar_t* c, float begin)
{
	
}

Meeting_t* findMeeting(Calendar_t* calendar)
{
	int i;
	float begin;
	
	for(i = 0; i < calendar->index; ++i)
	{
		if(calendar->meetings[i]->begin == begin)
		{
			return calendar->meetings[i];
		}
	}
	
	return NULL;
}

void destroyAD(Calendar_t* calendar)
{
	
}

void printAD(Calendar_t* calendar)
{
	int i;
	
	if(calendar == NULL || calendar->meetings == NULL)
	{
		return;
	}
	
	printf("My calendar: \n");
	
	for(i = 0; i < calendar->index; ++i)
	{
		if(calendar->meetings[i] == NULL)
		{
			return;
		}
		
		printMeeting(calendar->meetings[i]);
	}
	
	printf("\n");
}

void printMeeting(Meeting_t* meeting)
{
	printf("Begin: %f\n", meeting->begin);
	printf("End: %f\n", meeting->end);
	printf("Room: %d\n", meeting->room);
}