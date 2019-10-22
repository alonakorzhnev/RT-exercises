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

        BinIO_t& operator>>(void* buf);
        BinIO_t& operator<<(const void* buf);
        void operator,(int len);
};