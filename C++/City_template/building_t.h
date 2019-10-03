#pragma once

using namespace std;

template <class BID>
class Buiding_t
{
    public:
        ~Buiding_t();
        Buiding_t();
        Buiding_t(const Buiding_t& b);
        Buiding_t& operator=(const Buiding_t& b);

        BID getBuildingID() const;
        void setBuildingID(BID newID);

    private:
        BID id;
};

template <class BID>
Buiding_t<BID>::~Buiding_t() {}

template <class BID>
Buiding_t<BID>::Buiding_t() {}

template <class BID>
Buiding_t<BID>::Buiding_t(const Buiding_t& b) {id = b.id;}

template <class BID>
Buiding_t<BID>& Buiding_t<BID>::operator=(const Buiding_t& b) {id = b.id; return *this;}

template <class BID>
BID Buiding_t<BID>::getBuildingID() const {return id;}

template <class BID>
void Buiding_t<BID>::setBuildingID(BID newID) {id = newID;}