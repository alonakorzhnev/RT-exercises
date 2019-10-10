#include "tContainer_t.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

void testVector();
void testList();

void printMenu();

int main()
{
    cout << "Choose type of container: 1 - vector, 2 - list" << endl;

    unsigned int type;
    cin >> type;

    switch(type)
    {
        case 1:
            testVector();
            break;
        
        case 2:
            testList();
            break;
        
        default:
            break;
    }

    return 0;
}

void testVector()
{
    tContainer_t<int, list<int*> > iVect;

    unsigned int option;
    bool cont = true;

    while (cont)
    {
        printMenu();

        cin >> option;
        switch(option)
        {
        case 1:
        {
            cout << "Enter value: " << endl;
            int value;
            cin >> value;
            iVect.pushBack(new int(value));
            break;
        }
        case 2:
            cout << iVect.getSize() << endl;
            break;
        case 3:
            cout << iVect.isEmpty() << endl;
            break;
        case 4:
            cout << *iVect.getFirst() << endl;
            break;
        case 5:
            cout << *iVect.getLast() << endl;
            break;
        case 6:
        {
            cout << "Enter value: " << endl;
            int value;
            cin >> value;
            
            try
            {
                int* findValue = iVect.findByValue(value);
                cout << *findValue << endl;
            }
            catch(string e)
            {
                cerr << e << endl;
            }

            break;
        }
        case 7:
        {
            cout << "Enter value: " << endl;
            int value;
            cin >> value;
            
            try
            {
                int* removedValue = iVect.removeByValue(value);
                cout << *removedValue << endl;
            }
            catch(string e)
            {
                cerr << e << endl;
            }

            break;
        }
        case 8:
            iVect.removeAll();
            break;
        case 9:
        {
            cout << "Enter value: " << endl;
            int value;
            cin >> value;
            
            try
            {
                iVect.deleteByValue(value);
            }
            catch(string e)
            {
                cerr << e << endl;
            }

            break;
        }
        case 10:
            iVect.deleteAll();
            break;
        case 11:
        {
            cout << "Enter index: " << endl;
            int index;
            cin >> index;  
            try
            {
                cout << *iVect[index] << endl;
            }
            catch(string e)
            {
                cerr << e << endl;
            }

            break;
        }       
        default:
            cont = false;
            break;
        }
    }
}

void testList()
{
    tContainer_t<int, vector<int*> > iList;

    unsigned int option;
    bool cont = true;

    while (cont)
    {
        printMenu();

        cin >> option;
        switch(option)
        {
        case 1:
        {
            cout << "Enter value: " << endl;
            int value;
            cin >> value;
            iList.pushBack(new int(value));
            break;
        }
        case 2:
            cout << iList.getSize() << endl;
            break;
        case 3:
            cout << iList.isEmpty() << endl;
            break;
        case 4:
            cout << *iList.getFirst() << endl;
            break;
        case 5:
            cout << *iList.getLast() << endl;
            break;
        case 6:
        {
            cout << "Enter value: " << endl;
            int value;
            cin >> value;
            
            try
            {
                int* findValue = iList.findByValue(value);
                cout << *findValue << endl;
            }
            catch(string e)
            {
                cerr << e << endl;
            }

            break;
        }
        case 7:
        {
            cout << "Enter value: " << endl;
            int value;
            cin >> value;
            
            try
            {
                int* removedValue = iList.removeByValue(value);
                cout << *removedValue << endl;
            }
            catch(string e)
            {
                cerr << e << endl;
            }

            break;
        }
        case 8:
            iList.removeAll();
            break;
        case 9:
        {
            cout << "Enter value: " << endl;
            int value;
            cin >> value;
            
            try
            {
                iList.deleteByValue(value);
            }
            catch(string e)
            {
                cerr << e << endl;
            }

            break;
        }
        case 10:
            iList.deleteAll();
            break;
        case 11:
        {
            cout << "Enter index: " << endl;
            int index;
            cin >> index;  
            try
            {
                cout << *iList[index] << endl;
            }
            catch(string e)
            {
                cerr << e << endl;
            }

            break;
        }       
        default:
            cont = false;
            break;
        }
    }
}

void printMenu()
{
    cout << "1. Add new element" << endl
            << "2. Get size" << endl
            << "3. Is empty" << endl
            << "4. Get first element" << endl
            << "5. Get last element" << endl
            << "6. Find by value" << endl
            << "7. Remove by value" << endl
            << "8. Remove all" << endl
            << "9. Delete by value" << endl
            << "10. Delete all" << endl
            << "11. Get element by value" << endl;
}