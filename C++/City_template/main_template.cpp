#include "building_t.h"
#include "street_t.h"
#include "city_t.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    Buiding_t<int> b;
    b.setBuildingID(12);
    cout << b.getBuildingID() << endl;

    Street_t<string, int> s;
    s.setStreetID("Herzel");
    cout << s.getStreetID() << endl;

    City_t<string, string, int> c;
    c.setCityID("Tel-Aviv");
    cout << c.getCityID() << endl;

    return 0;
}