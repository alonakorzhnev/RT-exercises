#pragma once
#include "car_t.h"
#include <string>
using namespace std;

class Bus_t:public Car_t
{
    public:
        ~Bus_t();
        Bus_t();
        Bus_t(unsigned int c);
        Bus_t(const Bus_t& b);

    private:
        unsigned int countSeats;
        unsigned int lineNumber;
};