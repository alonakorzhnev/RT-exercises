#include "binIO_t.h"

BinIO_t& BinIO_t::operator>>(int& val)
{
    return fileToVal<int>(val);
}

BinIO_t& BinIO_t::operator<<(int val)
{
    return valToFile<int>(val);
}

/*BinIO_t& BinIO_t::operator>>(short& val) {}
BinIO_t& BinIO_t::operator<<(short val) {}
        
BinIO_t& BinIO_t::operator>>(unsigned short& val) {}
BinIO_t& BinIO_t::operator<<(unsigned short val) {}

BinIO_t& BinIO_t::operator>>(int& val) {}
BinIO_t& BinIO_t::operator<<(int val) {}

BinIO_t& BinIO_t::operator>>(unsigned int& val) {}
BinIO_t& BinIO_t::operator<<(unsigned int val) {}

BinIO_t& BinIO_t::operator>>(long& val) {}
BinIO_t& BinIO_t::operator<<(long val) {}

BinIO_t& BinIO_t::operator>>(unsigned long& val) {}
BinIO_t& BinIO_t::operator<<(unsigned long val) {}

BinIO_t& BinIO_t::operator>>(float& val) {}
BinIO_t& BinIO_t::operator<<(float val) {}

BinIO_t& BinIO_t::operator>>(double& val) {}
BinIO_t& BinIO_t::operator<<(double val) {}*/

BinIO_t& BinIO_t::operator>>(void* buf)
{
    m_rightShift = buf;
    return *this;
}

BinIO_t& BinIO_t::operator<<(const void* buf)
{
    m_leftShift = (void*)buf;
    return *this;
}

void BinIO_t::operator,(int len)
{
    if(m_rightShift)
    {
        if(validRead())
        {
            fread(m_rightShift, len, 1, m_fp);
            m_rightShift = 0;
        }
        else
        {
            m_status = readErr_e;
            throw string("Read error");
        }
    }
    else if(m_leftShift)
    {
        if(validWrite())
        {
            fwrite((const void*)m_leftShift, len, 1, m_fp);
            m_leftShift = 0;
        }
        else
        {
            m_status = writeErr_e;
            throw string("Write error");
        }
    }
}