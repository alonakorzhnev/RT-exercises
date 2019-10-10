#pragma once
#include <string>

using namespace std;

class Meeting_t
{
    public:
        ~Meeting_t() {}
        Meeting_t(float begin, float end, const string& subject);

        float getBegin() const {return m_begin;}
        float getEnd() const {return m_end;}
        const string& getSubject() const {return m_subject;}

    private:
        Meeting_t(const Meeting_t& m);
        Meeting_t& operator=(const Meeting_t& m);
        
        const float m_begin;
        const float m_end;
        const string m_subject;

        bool checkTime(float begin, float end);
};