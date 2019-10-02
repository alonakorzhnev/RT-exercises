#include "memManager_t.h"

MemManager_t::MemManager_t()
{
    memFull = false;
    actualSize = 0;
    currPosition = 0;
}

void MemManager_t::setCurrPosition(size_t pos)
{
    if(pos >= actualSize)
    {
        currPosition = actualSize;
    }
    else
    {
        throw string("Invalid position");
    }    
}

void MemManager_t::setActualSize(size_t writeCount)
{
    if((currPosition + writeCount) > actualSize)
    {
        actualSize = currPosition + writeCount;
    }
}