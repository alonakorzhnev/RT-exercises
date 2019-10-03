#pragma once
#include "building_t.h"
#include <vector>
#include <string>

using namespace std;

template <class SID, class BID>
class Street_t
{
    public:
        ~Street_t();
        Street_t();
        Street_t(const Street_t& s);
        Street_t& operator=(const Street_t& s);

        SID getStreetID() const;
        void setStreetID(SID newID);
        void addBuilding2Street(const Buiding_t<BID>& b);
        const Buiding_t<BID>& getBuilding(BID id) const;

    private:
        SID id;
        vector<Buiding_t<BID> > buildings;
};

template <class SID, class BID>
Street_t<SID, BID>::~Street_t() {}

template <class SID, class BID>
Street_t<SID, BID>::Street_t() {}

template <class SID, class BID>
Street_t<SID, BID>::Street_t(const Street_t<SID, BID>& s) {id = s.id; buildings = s.buildings;}

template <class SID, class BID>
Street_t<SID, BID>& Street_t<SID, BID>::operator=(const Street_t<SID, BID>& s) 
{
    id = s.id; 
    buildings = s.buildings; 
    return *this;
}

template <class SID, class BID>
SID Street_t<SID, BID>::getStreetID() const {return id;}

template <class SID, class BID>
void Street_t<SID, BID>::setStreetID(SID newID) {id = newID;}

template <class SID, class BID>
void Street_t<SID, BID>::addBuilding2Street(const Buiding_t<BID>& b) 
{
    buildings.push_back(b);
}

template <class SID, class BID>
const Buiding_t<BID>& Street_t<SID, BID>::getBuilding(BID id) const 
{
    for(int i = 0; i < buildings.size(); ++i)
    {
        if(buildings[i].getBuildingID() == id)
        {
            return buildings[i];
        }
    }
    throw string("There is no such building");
}