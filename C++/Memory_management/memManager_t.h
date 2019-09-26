#pragma once
#include <cstdlib>
using namespace std;

class MemManager_t
{
    public:
        MemManager_t();

        size_t getCurrPosition() const {return currPosition;}
        void setCurrPosition(size_t pos);
        bool getMemStatus() const {return memStatus;}
        size_t getActualSize() const {return actualSize;}

        virtual size_t readData(void* buffer, size_t size) {return 0;}
        virtual size_t readData(void* buffer, size_t size, size_t pos) {return 0;}

        virtual size_t writeData(const void* buffer, size_t size) {return 0;}
        virtual size_t writeData(const void* buffer, size_t size, size_t pos) {return 0;}

    protected:
        virtual ~MemManager_t() {}      

    private:
        MemManager_t(const MemManager_t& mm) {}
        MemManager_t& operator=(const MemManager_t& mm) {}

        bool memStatus;
        size_t actualSize;
        size_t currPosition;
};