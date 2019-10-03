#pragma once
#include "building_t.h"
#include "street_t.h"

using namespace std;

template <class CID, class SID, class BID>
class City_t
{
    public:
        ~City_t();
        City_t();
        City_t(const City_t& c);
        City_t& operator=(const City_t& c);

        CID getCityID() const;
        void setCityID(CID newID);
        void addStreet2City(const Street_t<SID, BID>& s);
        const Street_t<SID, BID>& getStreet(SID id) const;

    private:
        CID id;
        vector<Street_t<SID, BID> > streets;
};

template <class CID, class SID, class BID>
City_t<CID, SID, BID>::~City_t() {}

template <class CID, class SID, class BID>
City_t<CID, SID, BID>::City_t() {}

template <class CID, class SID, class BID>
City_t<CID, SID, BID>::City_t(const City_t& c) {id = c.id; streets = c.streets;}

template <class CID, class SID, class BID>
City_t<CID, SID, BID>& City_t<CID, SID, BID>::operator=(const City_t& c)
{
    id = c.id; 
    streets = c.streets;
    return *this;
}

template <class CID, class SID, class BID>
CID City_t<CID, SID, BID>::getCityID() const {return id;}

template <class CID, class SID, class BID>
void City_t<CID, SID, BID>::setCityID(CID newID) {id = newID;}

template <class CID, class SID, class BID>
void City_t<CID, SID, BID>::addStreet2City(const Street_t<SID, BID>& s)
{
     streets.push_pack(s);
}

template <class CID, class SID, class BID>
const Street_t<SID, BID>& City_t<CID, SID, BID>::getStreet(SID id) const
{
    for(int i = 0; i < streets.size(); ++i)
    {
        if(streets.get == id)
        {
            return streets[i];
        }
    }
    throw string("There is no such street");
}