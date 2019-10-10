#include "Meeting_t.h"

Meeting_t::Meeting_t(float begin, float end, const string& subject) : m_begin(begin), m_end(end), m_subject(subject)
{
    if(invalidTime(begin, end))
    {
        throw string("Invalid time");
    }
}

bool invalidTime(float begin, float end)
{
    return (begin < 0 && end < 0 && begin > end && begin > 24 && end > 24);
}