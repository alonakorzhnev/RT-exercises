#include <stdio.h>
#include "h_td.h"

static const int daysArr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
static char* monthsArr[12] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December" };

int setTime(cTime_t* time, int hour, int min, int sec)
{
	if(time == NULL)
	{
		return -1;
	}
	
	if(hour < 0 || hour >23 || min < 0 || min > 59 || sec < 0 || sec > 59)
	{
		return -1;
	}
	
	time->m_sec = sec;
	time->m_min = min;
	time->m_hour = hour;
	
	return 0;
}

void printTime(cTime_t* time, int format)
{
	char* meridien;
	int hour;
	
	if(time == NULL)
	{
		return;
	}
	
	if(format == 1)
	{
		printf("%d:%d:%d\n\n", time->m_hour, time->m_min, time->m_sec);
	}
	else if(format == 2)
	{
		if(time->m_hour <= 12)
		{
			meridien = "AM";
			hour = time->m_hour;
		}
		else
		{
			meridien = "PM";
			hour = time->m_hour - 12;
		}		
		
		printf("%d:%d:%d %s\n\n", hour, time->m_min, time->m_sec, meridien);
	}
}

int getHour(cTime_t* time)
{
	if(time == NULL)
	{
		return -1;
	}
	
 	return time->m_hour;
}

int getMinutes(cTime_t* time)
{
	if(time == NULL)
	{
		return -1;
	}
	
	return time->m_min;
}

int getSeconds(cTime_t* time)
{
	if(time == NULL)
	{
		return -1;
	}
	
	return time->m_sec;
}

void addTimes(cTime_t* time1, cTime_t* time2)
{
	int sec, min, hour;
	
	if(time1 == NULL || time2 == NULL)
	{
		return;
	}
	
	sec = time1->m_sec + time2->m_sec;
	min = time1->m_min + time2->m_min + sec/60;
	hour = time1->m_hour + time2->m_hour + min/60;
	hour = hour%24;
	min = min%60;
	sec = sec%60;
	
	setTime(time1, hour, min, sec);
}

int setDate(cDate_t* date, int day, int month, int year)
{
	if(date == NULL)
	{
		return -1;
	}
	
	if(day < 0 || day > 31 || month < 0 || month > 12 || year < 0)
	{
		return -1;
	}
	
	if(day > daysArr[month])
	{
		return -1;
	}
	
	if(!leapYear(date) && month == 2 && day == 29)
	{
		return -1;
	}		
	
	date->m_day = day;
	date->m_month = month;
	date->m_year = year;
	
	return 0;
}
	
void printDate(cDate_t* date, int format)
{
	if(date == NULL)
	{
		return;
	}
	
	if(format == 1)
	{
		printf("%d/%s/%d\n\n", date->m_day, monthsArr[date->m_month - 1], date->m_year);
	}
	else if(format == 2)
	{
		printf("%d/%d/%d\n\n", date->m_day, date->m_month, date->m_year);
	}
	else if(format == 3)
	{
		printf("%d/%d/%d\n\n", date->m_month, date->m_day, date->m_year);
	}
}

int getDays(cDate_t* date)
{
	if(date == NULL)
	{
		return -1;
	}
	
	return date->m_year;
}

int getMonths(cDate_t* date)
{
	if(date == NULL)
	{
		return -1;
	}
	
	return date->m_month;
}

int getYears(cDate_t* date)
{
	if(date == NULL)
	{
		return -1;
	}
	
	return date->m_year;
}

void addDays(cDate_t* date, int days)
{
	int i;
	int day = date->m_day, month = date->m_month, year = date->m_year;
		
	if(date == NULL)
	{
		return;
	}
	
	for (i = 0; i < days; i++)
        {
                day++;
                if(day > daysArr[month-1] || (month == 2 && day == 29 && !leapYear(date)))
                {
                    day = 1;
                    month++;
                    if(month == 13)
                    {
                        month = 1;
                        year++;
                    }
                }
        }
	setDate(date, day, month, year);
}

int leapYear(cDate_t* date)
{
	int year = date->m_year, isLeap = 0;
	
	if(date == NULL)
	{
		return -1;
	}
	
	if(year%4 == 0)
    {
        if( year%100 == 0)
        {
            if(year%400 == 0)
                isLeap = 1;
            else
                isLeap = 0;
        }
        else
            isLeap = 1;
    }
    else
        isLeap = 0;
	
	return isLeap;
}

char* getNameOfMonth(cDate_t* date)
{
	if(date == NULL)
	{
		return NULL;
	}
	
	return monthsArr[date->m_month];
}

int getNumberOfDay(cDate_t* date)
{
	int days_in_feb = 28;
	int result = date->m_day;
	
	if(date == NULL)
	{
		return -1;
	}	
	
	if(leapYear(date))
	{
		days_in_feb = 29;
	}
	
	switch(date->m_month)
    {
        case 2:
            result += 31;
            break;
        case 3:
            result += 31+days_in_feb;
            break;
        case 4:
            result += 31+days_in_feb+31;
            break;
        case 5:
            result += 31+days_in_feb+31+30;
            break;
        case 6:
            result += 31+days_in_feb+31+30+31;
            break;
        case 7:
            result += 31+days_in_feb+31+30+31+30;
            break;            
        case 8:
            result += 31+days_in_feb+31+30+31+30+31;
            break;
        case 9:
            result += 31+days_in_feb+31+30+31+30+31+31;
            break;
        case 10:
            result += 31+days_in_feb+31+30+31+30+31+31+30;            
            break;            
        case 11:
            result += 31+days_in_feb+31+30+31+30+31+31+30+31;            
            break;                        
        case 12:
            result += 31+days_in_feb+31+30+31+30+31+31+30+31+30;            
            break;                                    
    }
	return result;
}

