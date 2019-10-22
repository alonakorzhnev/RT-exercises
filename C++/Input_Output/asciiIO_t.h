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

        VirtIO_t& operator>>(char& val);
        VirtIO_t& operator<<(char val);

        template <class T> void fileToVal(T& val, const string& format);
        template <class T> void valToFile(T val, const string& format);

        /*VirtIO_t& operator>>(unsigned char& val);
        VirtIO_t& operator<<(unsigned char val);

        VirtIO_t& operator>>(short& val);
        VirtIO_t& operator<<(short val);
        
        VirtIO_t& operator>>(unsigned short& val);
        VirtIO_t& operator<<(unsigned short val);

        VirtIO_t& operator>>(int& val);
        VirtIO_t& operator<<(int val);

        VirtIO_t& operator>>(unsigned int& val);
        VirtIO_t& operator<<(unsigned int val);

        VirtIO_t& operator>>(long& val);
        VirtIO_t& operator<<(long val);

        VirtIO_t& operator>>(unsigned long& val);
        VirtIO_t& operator<<(unsigned long val);

        VirtIO_t& operator>>(float& val);
        VirtIO_t& operator<<(float val);

        VirtIO_t& operator>>(double& val);
        VirtIO_t& operator<<(double val);*/
};

template <class T> 
void AsciiIO_t::fileToVal(T& val, const string& format)
{
   if(validRead())
   {
       if(fscanf(m_fp, format.c_str(), val) != 1)
       {
           m_status = readErr_e;
       }
   }
   else
   {
       throw string("Read forbidden");
   }   
}

template <class T> 
void AsciiIO_t::valToFile(T val, const string& format)
{
    if(validWrite())
    {
        if(fprintf(m_fp, format.c_str(), val) < 0)
        {
            m_status = writeErr_e;
        }
    }
    else
    {
        throw string("Write forbidden");
    } 
}