#pragma once
#include "Meeting_t.h"
#include <map>

using namespace std;

class Calendar_t
{
    public:
        ~Calendar_t();
        Calendar_t();

        void insert(const Meeting_t* meeting);
        void remove(float begin);
        Meeting_t* find(float begin) const;
        void clean();

        void saveToFile();
        void restoreFromFile();

    private:
        map<float, Meeting_t*> m_calendar;

        typedef typename map<float, Meeting_t*>::iterator iter;
        typedef typename map<float, Meeting_t*>::const_iterator iterConst;

        Calendar_t(const Calendar_t& calendar);
        Calendar_t& operator=(const Calendar_t& calendar);
};