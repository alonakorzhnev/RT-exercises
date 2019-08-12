#ifndef CALENDAR_H
#define CALENDAR_H

struct meeting{
    float begin, end;
    int room;
};
typedef struct meeting Meeting_t;

struct calendar{
    Meeting_t** meetings;
    int capacity;
    int index;
};
typedef struct calendar Calendar_t;



Calendar_t* createAD(int capacity);

Meeting_t* createMeeting();

int insertMeeting(Calendar_t* calendar, Meeting_t* meeting);

int removeMeeting(Calendar_t* calendar);

Meeting_t* findMeeting(Calendar_t* calendar);

void destroyAD(Calendar_t* calendar);

void printAD(Calendar_t* calendar);

void printMeeting(Meeting_t* meeting);

#endif
