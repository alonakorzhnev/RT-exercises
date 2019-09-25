#include "car_t.h"

unsigned int Car_t::defId = 0;

Car_t::Car_t(const Car_t& c): id(defId++)
{
    name = c.name;
    capacity = c.capacity;
    girType = c.girType;
}

Car_t& Car_t::operator=(const Car_t& c)
{
    name = c.name;
    capacity = c.capacity;
    girType = c.girType;
}

bool Car_t::operator<(const Car_t& c) const
{
    return capacity < c.capacity;
}

bool Car_t::compare(const Car_t& c) const
{
    return name == c.name;
}