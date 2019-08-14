#include <stdio.h>
#include "h_td.h"

int main()
{
	int cont = 1, hour, min, sec;
	unsigned int option;
	int result, day, month, year;
	int numberDays, isLeap;
	
	cTime_t time1, time2;
	cTime_t *timePtr1, *timePtr2;
	
	cDate_t date;
	cDate_t *datePtr;
	
	while (cont) {
		printf("Choose option:\n");
		printf("1: Set a new time to existing object and print in all formats\n");
		printf("2: Addition of one time object to another\n");
		printf("3: Set a new date to existing object and print in all formats\n");
		printf("4: Add days to the data\n");
		printf("5: Number day of year\n");
		printf("6: Leap year\n");
		printf("Any another number - stop \n");

		scanf("%x", &option);
		switch (option) {
			case 1:
				timePtr1 = &time1;							
				printf("Please enter hours, minutes and seconds: ");
				scanf("%d%d%d", &hour, &min, &sec);
				
				result = setTime(timePtr1, hour, min, sec);
				
				if(result == -1)
				{
					printf("You entered wrong time data.");
					break;
				}
				
				printTime(timePtr1, 1);
				printTime(timePtr1, 2);
				break;
			
			case 2:
				timePtr1 = &time1;							
				printf("Please enter hours, minutes and seconds for firs time object: ");
				scanf("%d%d%d", &hour, &min, &sec);
				
				result = setTime(timePtr1, hour, min, sec);
				
				if(result == -1)
				{
					printf("You entered wrong time data.");
					break;
				}
				
				printTime(timePtr1, 1);
				
				timePtr2 = &time2;							
				printf("Please enter hours, minutes and seconds for second time object: ");
				scanf("%d%d%d", &hour, &min, &sec);
				
				result = setTime(timePtr2, hour, min, sec);
				
				if(result == -1)
				{
					printf("You entered wrong time data.");
					break;
				}
				
				printTime(timePtr2, 1);
				
				addTimes(timePtr1, timePtr2);
				
				printf("Result: ");
				printTime(timePtr1, 1);
				
				break;
			
			case 3:
				datePtr = &date;							
				printf("Please enter days, months and years: ");
				scanf("%d%d%d", &day, &month, &year);
				
				result = setDate(datePtr, day, month, year);
				
				if(result == -1)
				{
					printf("You entered wrong date data.");
					break;
				}
				
				printDate(datePtr, 1);
				printDate(datePtr, 2);
				printDate(datePtr, 3);
								
				break;
				
			case 4:
				datePtr = &date;							
				printf("Please enter days, months and years: ");
				scanf("%d%d%d", &day, &month, &year);
				
				result = setDate(datePtr, day, month, year);
				
				if(result == -1)
				{
					printf("You entered wrong date data.");
					break;
				}
				
				printf("Please enter number of days to add: ");
				scanf("%d", &numberDays);
				
				addDays(datePtr, numberDays);
				
				printDate(datePtr, 1);
				
				break;
				
			case 5:				
				datePtr = &date;							
				printf("Please enter days, months and years: ");
				scanf("%d%d%d", &day, &month, &year);
				
				result = setDate(datePtr, day, month, year);
				
				if(result == -1)
				{
					printf("You entered wrong date data.");
					break;
				}
				
				numberDays = getNumberOfDay(datePtr);
				printf("Number days of year: %d\n\n", numberDays);			
				
				break;

			case 6:
				datePtr = &date;							
				printf("Please enter days, months and years: ");
				scanf("%d%d%d", &day, &month, &year);
				
				result = setDate(datePtr, day, month, year);
				
				if(result == -1)
				{
					printf("You entered wrong date data.");
					break;
				}
				
				isLeap = leapYear(datePtr);
				if(isLeap)
				{
					printf("Year is leap.\n\n");
				}
				else
				{
					printf("Year is not leap.\n\n");
				}
				
				break;
				
				
			default: 
				cont = 0;
				break;
		}
	}

	return 0;
}
