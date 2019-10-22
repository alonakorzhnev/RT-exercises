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
};

template <class T> 
void VirtIO_t::fin(T& val, const string& format)
{
   if(validRead())
   {
       fscanf(m_fp, format, val);
   }
   else
   {
       throw string("Read forbidden");
   }   
}

template <class T> 
void VirtIO_t::fout(T val, const string& format)
{
    if(validWrite())
    {
        fprintf(m_fp, format, val);
    }
    else
    {
        throw string("Write forbidden");
    } 
}