#pragma once
#include "car_t.h"
#include <string>
using namespace std;

class Private_t:public Car_t
{
    public:
        ~Private_t() {}
        Private_t();
        Private_t(unsigned int c);
        Private_t(const Private_t& p);

        Private_t& operator=(const Private_t& p) const;

        void accelerateSpeed() {speed += 10;}
        void reduceSpeed() {speed -= 10;}

    private:
        int speed;
};