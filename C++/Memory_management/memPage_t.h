#pragma once
#include "memManager_t.h"
#include <cstdlib>
using namespace std;

class MemPage_t : public MemManager_t
{
    public:
        ~MemPage_t();
        MemPage_t();
        MemPage_t(size_t cap);

        size_t getCapacity() const {return capacity;}

        virtual size_t readData(void* buffer, size_t size);
        virtual size_t readData(void* buffer, size_t size, size_t pos);

        virtual size_t writeData(const void* buffer, size_t size);
        virtual size_t writeData(const void* buffer, size_t size, size_t pos);

        static void getDefCapacity() {return defaultCapacity;}
        static size_t setDefCapacity(size_t cap) {defaultCapacity = cap;}

    private:
        MemPage_t(const MemPage_t& mp) {}
        MemPage_t& operator=(const MemPage_t& mp) {}

        char* stream;
        size_t capacity;
        static size_t defaultCapacity;
};