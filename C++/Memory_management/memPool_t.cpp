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
    if(buffer == 0 || size == 0)
    {
        return 0;
    }

    return readData(buffer, size);
}

size_t MemPool_t::read(void* buffer, size_t size, size_t pos)
{
    if(buffer == 0 || size == 0)
    {
        return 0;
    }

    setCurrPosition(pos);

    return readData(buffer, size);
}

size_t MemPool_t::write(const void* buffer, size_t size)
{
    if(buffer == 0 || size == 0)
    {
        return 0;
    }

    return writeData(buffer, size);
}

size_t MemPool_t::write(const void* buffer, size_t size, size_t pos)
{
    if(buffer == 0 || size == 0)
    {
        return 0;
    }

    setCurrPosition(pos);

    return writeData(buffer, size);
}

size_t MemPool_t::readData(void* buffer, size_t size)
{
    size_t pageIndex = currPosition/pageSize;
    size_t readSize = actualSize - currPosition, readCount, buffPos = 0;

    if(readSize < size)
    {
        size = readSize;
    }

    while(true)
    {
        pool[pageIndex]->setCurrPosition(currPosition%pageSize);
        readCount = pool[pageIndex]->read((char*)buffer + buffPos, readSize);
        setCurrPosition(currPosition + readCount);
        if(readCount != readSize)
        {
            readSize -= readCount;
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

size_t MemPool_t::writeData(const void* buffer, size_t size)
{
    size_t pageIndex = currPosition/pageSize;
    size_t writeCount, buffPos = 0, tempSize = size;

    while(true)
    {
        writeCount = pool[pageIndex]->write((char*)buffer + buffPos, tempSize);
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

    if((currPosition + size) > actualSize)
    {
        actualSize = currPosition + size;
    }
    
    return size;
}