#include "private_t.h"

Private_t::Private_t()
{
    setName("private");
    setCapacity(1500);
    setGir(Automatic);
}

Private_t::Private_t(unsigned int c):Car_t(c)
{
    setName("private");
    setGir(Automatic);
}

Private_t::Private_t(const Private_t& p)
{
    speed = p.speed;
}

Private_t& Private_t::operator=(const Private_t& p) const
{
    Car_t::operator=(p);
    speed = p.speed;
}