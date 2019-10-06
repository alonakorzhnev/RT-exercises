#pragma once
#include <string>

using namespace std;

template <class T>
class TException_t
{
    public:
        ~TException_t() {}
        TException_t(const T& exception, const string& message, const string& fileName, int lineNumber):
                m_exception(exception), m_message(message), 
                m_fileName(fileName), m_lineNumber(lineNumber) {}

        TException_t(const TException_t& ex) 
        {   
            m_exception = ex.m_exception;
            m_message = ex.m_message;
            m_fileName = ex.m_fileName;
            m_lineNumber = ex.m_lineNumber;
        }

        const T& getException() const {return m_exception;}
        const string& getMessage() const {return m_message;}
        const string& getFileName() const {return m_fileName;}
        int getLineNumber() const {return m_lineNumber;}

    private:
        T m_exception;
        string m_message;
        string m_fileName;
        int m_lineNumber;

        TException_t& operator=(const TException_t& ex);
};


