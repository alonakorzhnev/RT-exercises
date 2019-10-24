#pragma once
#include "virtIO_t.h"
#include <string>

using namespace std;

class AsciiIO_t : public VirtIO_t
{
    public:
        AsciiIO_t() {}
        AsciiIO_t(const string& name, const string& access) : VirtIO_t(name, access) {}
        ~AsciiIO_t() {}

        AsciiIO_t& operator>>(int& val);
        AsciiIO_t& operator<<(int val);

        AsciiIO_t& operator>>(float& val);
        AsciiIO_t& operator<<(float val);

        /*AsciiIO_t& operator>>(unsigned char& val);
        AsciiIO_t& operator<<(unsigned char val);

        AsciiIO_t& operator>>(short& val);
        AsciiIO_t& operator<<(short val);
        
        AsciiIO_t& operator>>(unsigned short& val);
        AsciiIO_t& operator<<(unsigned short val);

        AsciiIO_t& operator>>(unsigned int& val);
        AsciiIO_t& operator<<(unsigned int val);

        AsciiIO_t& operator>>(long& val);
        AsciiIO_t& operator<<(long val);

        AsciiIO_t& operator>>(unsigned long& val);
        AsciiIO_t& operator<<(unsigned long val);

        AsciiIO_t& operator>>(double& val);
        AsciiIO_t& operator<<(double val);*/

    private:
        template <class T> AsciiIO_t& fileToVal(T& val, const char* format);
        template <class T> AsciiIO_t& valToFile(T val, const char* format);
};

template <class T> 
AsciiIO_t& AsciiIO_t::fileToVal(T& val, const char* format)
{
    if(validRead())
    {
        fscanf(m_fp, format, &val);
        return *this;              
    }
    m_status = readErr_e;
    throw string("Read error");   
}

template <class T> 
AsciiIO_t& AsciiIO_t::valToFile(T val, const char* format)
{
    if(validWrite())
    {
        fprintf(m_fp, format, val);
        return *this;
    }
    m_status = writeErr_e;
    throw string("Write error");
}