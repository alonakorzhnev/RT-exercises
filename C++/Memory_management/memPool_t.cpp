#include "memPool_t.h"

MemPool_t::~MemPool_t()
{
    for(int i = 0; i < pool.size(); ++i)
    {
        delete pool[i];
    }
}

MemPool_t::MemPool_t()
{
    MemPage_t* pg = new MemPage_t;
    pool.push_back(pg);
    pageSize = pg->getCapacity();
}

size_t MemPool_t::read(void* buffer, size_t size)
{
    return read(buffer, size, currPosition);
}

size_t MemPool_t::read(void* buffer, size_t size, size_t pos)
{
    if(buffer == 0 || size == 0)
    {
        return 0;
    }

    setCurrPosition(pos);
    size_t pageIndex = currPosition/pageSize;
    size_t tempSize, readCount, buffPos = 0;

    if(size > (actualSize - currPosition))
    {
        size = actualSize - currPosition;
    }
    tempSize = size;
        
    while(true)
    {
        pool[pageIndex]->setCurrPosition(currPosition%pageSize);
        readCount = pool[pageIndex]->read((char*)buffer + buffPos, tempSize);
        setCurrPosition(currPosition + readCount);

        if(readCount != tempSize)
        {
            tempSize -= readCount;
            buffPos += readCount;
            pageIndex++;
        }
        else
        {
            break;
        }
    }

    return size;
}

size_t MemPool_t::write(const void* buffer, size_t size)
{
    return write(buffer, size, currPosition);
}

size_t MemPool_t::write(const void* buffer, size_t size, size_t pos)
{
    if(buffer == 0 || size == 0)
    {
        return 0;
    }

    setCurrPosition(pos);
    size_t pageIndex = currPosition/pageSize;
    size_t writeCount, buffPos = 0, tempSize = size;

    while(true)
    {
        pool[pageIndex]->setCurrPosition(currPosition%pageSize);
        writeCount = pool[pageIndex]->write((char*)buffer + buffPos, tempSize);
        setActualSize(writeCount);
        setCurrPosition(currPosition + writeCount); 

        if(writeCount != tempSize)
        {
            MemPage_t* pg = new MemPage_t;
            pool.push_back(pg);

            tempSize -= writeCount;
            buffPos += writeCount;
            pageIndex++;
        }
        else
        {
            break;
        }
    }
    
    return size;
}