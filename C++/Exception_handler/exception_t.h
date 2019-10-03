#pragma once
#include <string>

using namespace std;

template <class T>
class TException_t
{
    public:
        TException_t(T exception, string message, string fileName, int lineNumber);

        const T& getException() const {return m_exception;}
        string getMessage() const {return m_message;}
        string getFileName() const {return m_fileName;}
        int getLineNumber() const {return m_lineNumber;}

    private:
        T m_exception;
        string m_message;
        string m_fileName;
        int m_lineNumber;
};

template <class T>
TException_t<T>::TException_t(T exception, string message, string fileName, int lineNumber)
{
    m_exception = exception;
    m_message = message;
    m_fileName = fileName;
    m_lineNumber = lineNumber;
}

