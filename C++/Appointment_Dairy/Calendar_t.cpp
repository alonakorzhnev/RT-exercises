#include "Calendar_t.h"

void Calendar_t::insert(const Meeting_t* meeting)
{
    if(meeting == 0)
    {
        return;
    }

    if(m_calendar.empty())
    {
        m_calendar.insert(pair<float, Meeting_t*>(meeting->getBegin(), meeting));
    }
    else if()
    {
        iter = m_calendar.find(meeting->getBegin());
    }
    


    
}

void Calendar_t::remove(float begin)
{

}

Meeting_t* Calendar_t::find(float begin) const
{

}

void Calendar_t::clean()
{

}