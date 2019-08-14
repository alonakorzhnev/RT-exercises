#include "h_td.h"

void setTime(cTime_t* time, int sec, int min, int hour)
{
	time.m_sec = sec;
	time.m_min = min;
	time.m_hour = hour;
}

void printTime(cTime_t* time, int format)
{
	char meridien[4];
	int hour;
	
	if(format == 1)
	{
		printf("%d:%d:%d\n", time.m_hour, time.m_min, time.m_sec);
	}
	else if(format == 2)
	{
		if(time.m_hour <= 12)
		{
			meridien = "AM";
			hour = time.m_hour;
		}
		else
		{
			meridien = "PM";
			hour = time.m_hour - 12;
		}		
		
		printf("%d:%d:%d\n", time.m_hour, time.m_min, time.m_sec);
	}
}

int getHour(cTime_t* time)
{
 	return time->m_hour;
}

int getMinutes(cTime_t* time)
{
	return time->m_min;
}

int getSeconds(cTime_t* time)
{

}

void addTimes(cTime_t* time1, cTime_t* time2);
{

}