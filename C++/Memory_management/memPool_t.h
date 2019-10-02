#pragma once
#include "memManager_t.h"
#include "memPage_t.h"
#include <cstdlib>
#include <vector>
using namespace std;

class MemPool_t : public MemManager_t
{
    public:
        ~MemPool_t();
        MemPool_t();

        virtual size_t read(void* buffer, size_t size);
        virtual size_t read(void* buffer, size_t size, size_t pos);

        virtual size_t write(const void* buffer, size_t size);
        virtual size_t write(const void* buffer, size_t size, size_t pos);

    private:
        MemPool_t(const MemPool_t& mp);
        MemPool_t& operator=(const MemPool_t& mp);

        vector<MemPage_t*> pool;
        size_t pageSize;

        size_t readData(void* buffer, size_t size);
        size_t writeData(const void* buffer, size_t size);
};