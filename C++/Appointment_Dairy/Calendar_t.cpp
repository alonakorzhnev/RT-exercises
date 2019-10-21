#include "Calendar_t.h"

Meeting_t* Calendar_t::createMeeting(float begin, float end, const string& subject)
{
    if (begin > 0 && end > 0 && begin < end && begin < 24 && end < 24)
    {
        return new Meeting_t(begin, end, subject);
    }
    return 0;
}

bool Calendar_t::insertMeeting(const Meeting_t* meeting)
{
    if (meeting == 0)
    {
        return false;
    }

    bool flagInsert = false;

    if (m_calendar.empty() ||
        (m_calendar.begin())->first > meeting->getEnd() ||
        (((--m_calendar.end())->second)->getEnd() < meeting->getBegin()))
    {
        flagInsert = true;
    }
    else
    {
        iter it = m_calendar.find(meeting->getBegin());
        if (it == m_calendar.end())
        {
            it = m_calendar.lower_bound(meeting->getBegin());
            if (it->first >= meeting->getEnd())
            {
                flagInsert = true;
            }
        }
    }

    if (flagInsert)
    {
        m_calendar[meeting->getBegin()] = (Meeting_t*)meeting;
        return true;
    }
    else
    {
        delete meeting;
        return false;
    }
}

bool Calendar_t::removeMeeting(float begin)
{
    iter it = m_calendar.find(begin);
    if (it != m_calendar.end())
    {
        delete it->second;
        m_calendar.erase(it);
        return true;
    }
    return false;
}

Meeting_t* Calendar_t::findMeeting(float begin) const
{
    iterConst it = m_calendar.find(begin);
    return (it != m_calendar.end()) ? it->second : 0;
}

void Calendar_t::clean()
{
    for (iter it = m_calendar.begin(); it != m_calendar.end(); ++it)
    {
        delete it->second;
    }
    m_calendar.clear();
}

void Calendar_t::print() const
{
    for (iterConst it = m_calendar.begin(); it != m_calendar.end(); ++it)
    {
        cout  << endl << "Meeting begin hour: "  << it->second->getBegin()   << endl
                      << "        end hour: "    << it->second->getEnd()     << endl
                      << "        subject: "     << it->second->getSubject() << endl
                      << endl;
    }
}