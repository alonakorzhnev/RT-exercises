#pragma once
#include "Meeting_t.h"
#include <map>
#include <iostream>

using namespace std;

class Calendar_t
{
public:
    ~Calendar_t() {}
    Calendar_t() {}

    Meeting_t* createMeeting(float begin, float end, const string& subject);
    bool insertMeeting(const Meeting_t* meeting);
    bool removeMeeting(float begin);
    Meeting_t* findMeeting(float begin) const;
    void clean();
    void print() const;

    void saveToFile();
    void restoreFromFile();

private:
    map<float, Meeting_t*> m_calendar;

    typedef typename map<float, Meeting_t*>::iterator iter;
    typedef typename map<float, Meeting_t*>::const_iterator iterConst;

    Calendar_t(const Calendar_t& calendar);
    Calendar_t& operator=(const Calendar_t& calendar);
};