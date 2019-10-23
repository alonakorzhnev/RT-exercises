#pragma once
#include "virtIO_t.h"
#include <string>

using namespace std;

class BinIO_t : public VirtIO_t
{
    public:
        BinIO_t() : m_leftShift(0), m_rightShift(0) {}
        BinIO_t(const string& name, const string& access) : VirtIO_t(name, access), m_leftShift(0), m_rightShift(0) {}
        ~BinIO_t() {}

        BinIO_t& operator>>(int& val);
        BinIO_t& operator<<(int val);

        /*BinIO_t& operator>>(unsigned char& val);
        BinIO_t& operator<<(unsigned char val);

        BinIO_t& operator>>(short& val);
        BinIO_t& operator<<(short val);
        
        BinIO_t& operator>>(unsigned short& val);
        BinIO_t& operator<<(unsigned short val);

        BinIO_t& operator>>(int& val);
        BinIO_t& operator<<(int val);

        BinIO_t& operator>>(unsigned int& val);
        BinIO_t& operator<<(unsigned int val);

        BinIO_t& operator>>(long& val);
        BinIO_t& operator<<(long val);

        BinIO_t& operator>>(unsigned long& val);
        BinIO_t& operator<<(unsigned long val);

        BinIO_t& operator>>(float& val);
        BinIO_t& operator<<(float val);

        BinIO_t& operator>>(double& val);
        BinIO_t& operator<<(double val);*/

        BinIO_t& operator>>(void* buf);
        BinIO_t& operator<<(const void* buf);
        void operator,(int len);

    private:
        template <class T> BinIO_t& fileToVal(T& val);
        template <class T> BinIO_t& valToFile(T val);

        void* m_leftShift;
        void* m_rightShift;
};

template <class T> 
BinIO_t& BinIO_t::fileToVal(T& val)
{
     *this >> &val, sizeof(T);
}

template <class T> 
BinIO_t& BinIO_t::valToFile(T val)
{
    *this << &val, sizeof(T);
}