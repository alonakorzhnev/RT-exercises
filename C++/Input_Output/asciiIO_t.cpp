#include "asciiIO_t.h"

AsciiIO_t& AsciiIO_t::operator>>(int& val)
{
    return fileToVal<int>(val, "%d");
}

AsciiIO_t& AsciiIO_t::operator<<(int val)
{
    return valToFile<int>(val, "%d");
}

/*AsciiIO_t& AsciiIO_t::operator>>(unsigned char& val) {}
AsciiIO_t& AsciiIO_t::operator<<(unsigned char val) {}

AsciiIO_t& AsciiIO_t::operator>>(short& val) {}
AsciiIO_t& AsciiIO_t::operator<<(short val) {}
        
AsciiIO_t& AsciiIO_t::operator>>(unsigned short& val) {}
AsciiIO_t& AsciiIO_t::operator<<(unsigned short val) {}

AsciiIO_t& AsciiIO_t::operator>>(int& val) {}
AsciiIO_t& AsciiIO_t::operator<<(int val) {}

AsciiIO_t& AsciiIO_t::operator>>(unsigned int& val) {}
AsciiIO_t& AsciiIO_t::operator<<(unsigned int val) {}

AsciiIO_t& AsciiIO_t::operator>>(long& val) {}
AsciiIO_t& AsciiIO_t::operator<<(long val) {}

AsciiIO_t& AsciiIO_t::operator>>(unsigned long& val) {}
AsciiIO_t& AsciiIO_t::operator<<(unsigned long val) {}

AsciiIO_t& AsciiIO_t::operator>>(float& val) {}
AsciiIO_t& AsciiIO_t::operator<<(float val) {}

AsciiIO_t& AsciiIO_t::operator>>(double& val) {}
AsciiIO_t& AsciiIO_t::operator<<(double val) {}*/