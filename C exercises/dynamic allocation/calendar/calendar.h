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

int insertMeeting(Calendar_t* c, Meeting_t* m);

int removeMeeting(Calendar_t* c, float begin);

Meeting_t* findMeeting(Calendar_t* c);

void destroyAD(Calendar_t* c);

void printAD(Calendar_t* c);

void printMeeting(Meeting_t* m);

#endif
