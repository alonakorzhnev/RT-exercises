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
	
	printf("\nCalendar has been created.\n\n");
	return calendar;
}

Meeting_t* createMeeting(float begin, float end, int room)
{
	Meeting_t* meeting;
	
	meeting = (Meeting_t*)malloc(sizeof(Meeting_t));
	
	if(meeting == NULL)
	{
		return NULL;
	}
	
	meeting->begin = begin;
	meeting->end = end;
	meeting->room = room;	
	
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
				break;
			}
		}
	}
	
	if(insert_index == -1) /*meetings overlap*/
	{
		printf("\nMeetings overlap! Please choose another time.\n\n");
		free(meeting);
		return -1;
	}
	
	if(calendar->index == calendar->capacity) /*memory allocation*/
	{
		temp = calendar->meetings;
		calendar->meetings = (Meeting_t**)realloc(calendar->meetings, (calendar->capacity*2)*sizeof(Meeting_t*));
		
		if(calendar->meetings == NULL)
		{
			calendar->meetings = temp;
			free(meeting);
			return -1;
		}
		
		printf("Memory allocation.\n");
		(calendar->capacity) *= 2;
	}

	if(insert_index != calendar->index) /*shift right*/
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

int removeMeeting(Calendar_t* calendar)
{
	int i, index_remove = -1;
	float begin;
	Meeting_t* temp;
	
	if(calendar == NULL)
	{
		return -1;
	}
	
	printf("Enter begin time: ");
	scanf("%f", &begin);
	
	for(i = 0; i < calendar->index; ++i) /*find index of meeting*/
	{
		if(calendar->meetings[i]->begin == begin)
		{
			index_remove = i;
			break;
		}
	}
	
	if(index_remove == -1) /*meeting not found*/
	{		
		return -1;
	}
	
	free(calendar->meetings[index_remove]); /*remove meeting*/
		
	(calendar->index)--;
	
	return 0;
}

Meeting_t* findMeeting(Calendar_t* calendar)
{
	int i;
	float begin;
	
	printf("Enter begin time: ");
	scanf("%f", &begin);
	
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
	int i;
	
	if(calendar == NULL)
	{
		return;
	}
	
	for(i = 0; i < calendar->index; ++i)
	{
		free(calendar->meetings[i]);
	}
	
	free(calendar->meetings);
	free(calendar);
}

void printAD(Calendar_t* calendar)
{
	int i;
	
	if(calendar == NULL)
	{
		return;
	}
	
	printf("My calendar: \n\n");
	
	for(i = 0; i < calendar->index; ++i)
	{	
		printMeeting(calendar->meetings[i]);
		printf("\n");
	}
}

void printMeeting(Meeting_t* meeting)
{
	printf("Begin: %.2f\n", meeting->begin);
	printf("End: %.2f\n", meeting->end);
	printf("Room: %d\n", meeting->room);
}

int loadFromFile(Calendar_t* calendar)
{
	FILE* fp;
	int room, flag_success;
	float begin, end;
	Meeting_t* meeting;	
	
	if(calendar == NULL)
	{
		return -1;
	}
	
	if((fp = fopen("Calendar.txt", "r")) == NULL)
	{
		return 1;
	}
	
	while(1)
	{
		fscanf(fp, "%f%f%d", &begin, &end, &room);
		
		if(!feof(fp))
		{
			meeting = createMeeting(begin, end, room);
				
			if(meeting == NULL)
			{
				return -1;
			}

			flag_success = insertMeeting(calendar, meeting);

			if(flag_success == -1)
			{
				return -1;
			}
		}
		else
		{
			break;
		}
	}
	
	if(fclose(fp) != 0)
	{
		return -1;
	}
	
	return 0;
}

int saveInFile(Calendar_t* calendar)
{
	FILE* fp;
	int room, i;
	float begin, end;
	
	if((fp = fopen("Calendar.txt", "w")) == NULL || calendar == NULL)
	{
		return -1;
	}
	
	for(i = 0; i < calendar->index; ++i)
	{	
		fprintf(fp, "\n%0.2f\n%0.2f\n%d", calendar->meetings[i]->begin, 
				calendar->meetings[i]->end, calendar->meetings[i]->room);		
	}
	
	if(fclose(fp) != 0)
	{
		return -1;
	}
	
	return 0;
}
	