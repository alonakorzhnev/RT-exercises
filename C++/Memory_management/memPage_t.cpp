#include "memPage_t.h"
#include <cstring>

size_t MemPage_t::defaultCap = 6;

MemPage_t::~MemPage_t()
{
    delete[] stream;
}

MemPage_t::MemPage_t()
{
    stream = new char[defaultCap];
    capacity = defaultCap;
}

MemPage_t::MemPage_t(size_t cap)
{
    stream = new char[cap];
    capacity = cap;
}

size_t MemPage_t::read(void* buffer, size_t size)
{
    return read(buffer, size, currPosition);
}

size_t MemPage_t::read(void* buffer, size_t size, size_t pos)
{
    if(buffer == 0 || size == 0)
    {
        return 0;
    }

    setCurrPosition(pos);
    size_t readCount = actualSize - currPosition;

    if(readCount < size)
    {
        size = readCount;
    }

    memcpy(buffer, stream + currPosition, size);
    setCurrPosition(currPosition + size);

    return size;
}

size_t MemPage_t::write(const void* buffer, size_t size)
{
    return write(buffer, size, currPosition);
}

size_t MemPage_t::write(const void* buffer, size_t size, size_t pos)
{
    if(buffer == 0 || size == 0)
    {
        return 0;
    }

    setCurrPosition(pos);
    size_t writeCount = capacity - currPosition;

    if(size > writeCount)
    {
        size = writeCount;
    }
    
    memcpy(stream + currPosition, buffer, size);
    setActualSize(size);
    setCurrPosition(currPosition + size);

    if(actualSize == capacity)
    {
        memFull = true;
    }

    return size;    
}


