#include "binIO_t.h"

VirtIO_t& operator>>(char& val) {}
VirtIO_t& operator<<(char val) {}

VirtIO_t& operator>>(unsigned char& val) {}
VirtIO_t& operator<<(unsigned char val) {}

VirtIO_t& operator>>(short& val) {}
VirtIO_t& operator<<(short val) {}
        
VirtIO_t& operator>>(unsigned short& val) {}
VirtIO_t& operator<<(unsigned short val) {}

VirtIO_t& operator>>(int& val) {}
VirtIO_t& operator<<(int val) {}

VirtIO_t& operator>>(unsigned int& val) {}
VirtIO_t& operator<<(unsigned int val) {}

VirtIO_t& operator>>(long& val) {}
VirtIO_t& operator<<(long val) {}

VirtIO_t& operator>>(unsigned long& val) {}
VirtIO_t& operator<<(unsigned long val) {}

VirtIO_t& operator>>(float& val) {}
VirtIO_t& operator<<(float val) {}

VirtIO_t& operator>>(double& val) {}
VirtIO_t& operator<<(double val) {}

BinIO_t& BinIO_t::operator>>(void* buf)
{

}

BinIO_t& BinIO_t::operator<<(const void* buf)
{

}

void BinIO_t::operator,(int len)
{

}