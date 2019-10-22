#include "asciiIO_t.h"

VirtIO_t& AsciiIO_t::operator>>(char& val)
{
    fileToVal<char>(val, "%c");
}

VirtIO_t& AsciiIO_t::operator<<(char val)
{
    valToFile<char>(val, "%c");
}

/*VirtIO_t& VirtIO_t::operator>>(unsigned char& val) {}
VirtIO_t& VirtIO_t::operator<<(unsigned char val) {}

VirtIO_t& VirtIO_t::operator>>(short& val) {}
VirtIO_t& VirtIO_t::operator<<(short val) {}
        
VirtIO_t& VirtIO_t::operator>>(unsigned short& val) {}
VirtIO_t& VirtIO_t::operator<<(unsigned short val) {}

VirtIO_t& VirtIO_t::operator>>(int& val) {}
VirtIO_t& VirtIO_t::operator<<(int val) {}

VirtIO_t& VirtIO_t::operator>>(unsigned int& val) {}
VirtIO_t& VirtIO_t::operator<<(unsigned int val) {}

VirtIO_t& VirtIO_t::operator>>(long& val) {}
VirtIO_t& VirtIO_t::operator<<(long val) {}

VirtIO_t& VirtIO_t::operator>>(unsigned long& val) {}
VirtIO_t& VirtIO_t::operator<<(unsigned long val) {}

VirtIO_t& VirtIO_t::operator>>(float& val) {}
VirtIO_t& VirtIO_t::operator<<(float val) {}

VirtIO_t& VirtIO_t::operator>>(double& val) {}
VirtIO_t& VirtIO_t::operator<<(double val) {}*/