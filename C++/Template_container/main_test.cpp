#include "tContainer_t.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

void testVector();
void testList();

int main()
{
    testVector();
    testList();

    return 0;
}

void testVector()
{
    tContainer_t<int, list<int*> > iVect;

    for(int i = 0; i < 10; ++i)
    {
        iVect.pushBack(new int(i));
    }

    cout << iVect.getSize() << endl;
    cout << *iVect.getFirst() << endl;
    cout << *iVect.getLast() << endl;

    try
    {
        int* findValue = iVect.findByValue(5);
        cout << *findValue << endl;
    }
    catch(string e)
    {
        cerr << e << endl;
    }
    
    try
    {
        int* removeValue = iVect.removeByValue(6);
        cout << *removeValue << endl;
        cout << iVect.getSize() << endl;
    }
    catch(string e)
    {
        cerr << e << endl;
    }

    cout << *iVect[3] << endl;

    iVect.deleteAll();
}

void testList()
{
    tContainer_t<int, vector<int*> > iList;

    for(int i = 10; i < 20; ++i)
    {
        iList.pushBack(new int(i));
    }

    cout << iList.getSize() << endl;
    cout << *iList.getFirst() << endl;
    cout << *iList.getLast() << endl;

    try
    {
        int* findValue = iList.findByValue(5);
        cout << *findValue << endl;
    }
    catch(string e)
    {
        cerr << e << endl;
    }
    
    try
    {
        int* removeValue = iList.removeByValue(16);
        cout << *removeValue << endl;
        cout << iList.getSize() << endl;
    }
    catch(string e)
    {
        cerr << e << endl;
    }

    cout << *iList[3] << endl;

    iList.deleteAll();
}