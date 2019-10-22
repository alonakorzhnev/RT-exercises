#pragma once
#include "virtIO_t.h"
#include <string>

using namespace std;

class BinIO_t : public VirtIO_t
{
    public:
        BinIO_t() {}
        BinIO_t(const string& name, const string& access) : VirtIO_t(name, access) {}
        ~BinIO_t() {}

        template <class T> void fileToVal(T& val);
        template <class T> void valToFile(T val);

        VirtIO_t& operator>>(char& val);
        VirtIO_t& operator<<(char val);

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

        BinIO_t& operator>>(void* buf);
        BinIO_t& operator<<(const void* buf);
        void operator,(int len);
};

template <class T> 
void BinIO_t::fileToVal(T& val)
{
   if(validRead())
   {
       fread(&val, sizeof(T), 1, m_fp);
   }
   else
   {
       throw string("Read forbidden");
   }   
}

template <class T> 
void BinIO_t::valToFile(T val)
{
    if(validWrite())
    {
        fwrite((const void*)&val, sizeof(T), 1, m_fp);
    }
    else
    {
        throw string("Write forbidden");
    } 
}