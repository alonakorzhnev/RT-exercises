#ifndef H_TD
#define H_TD

typedef struct
{
	int m_sec;
	int m_min;
	int m_hour;
	
}cTime_t;

int setTime(cTime_t* time, int hour, int min, int sec);
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

int setDate(cDate_t* date, int day, int month, int year);
void printDate(cDate_t* date, int format);
int getDays(cDate_t* date);
int getMonths(cDate_t* date);
int getYears(cDate_t* date);
void addDates(cDate_t* date1, cDate_t* date2);
int getNumberOfDay(cDate_t* date);
char* getNameOfMonth(cDate_t* date);
int leapYear(cDate_t* date);

#endif
