#ifndef H_TD
#define H_TD

typedef struct
{
	int m_sec;
	int m_min;
	int m_hour;
	
}cTime_t;

void setTime(cTime_t* time, int sec, int min, int hour);
void printTime(cTime_t* time, int format);
int getHours(cTime_t* time);
int getMinutes(cTime_t* time);
int getSeconds(cTime_t* time);
void addTimes(cTime_t* time1, cTime_t* time2);

typedef struct
{
	int m_day;
	int m_month;
	int m_year;
	
}cDate_t;

#endif
