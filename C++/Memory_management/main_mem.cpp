#include "memPage_t.h"
#include "memPool_t.h"
#include <iostream>
using namespace std;

void test(MemManager_t* m);

int main()
{
    size_t option;
    MemManager_t* mptr;

    cout << "Choose object: 1-MemPage, 2-MemPool" << endl;
    cin >> option;

    switch (option)
    {
    case 1:
        mptr = new MemPage_t;
        break;

    case 2:
        mptr = new MemPool_t;
        break;
    
    default:
        break;
    }

    test(mptr);
    delete mptr;

    return 0;
}

void test(MemManager_t* m)
{

    char buffer[32];
    memset(&buffer, '\0', sizeof(buffer));
    size_t count, option, position, size;
    bool cont = true;

    while(cont)
    {
        cout    << "1. Write with position"     << endl
                << "2. Write without position"  << endl
                << "3. Read with position"      << endl
                << "4. Read without position"   << endl
                << "5. Set position"            << endl
                << "Any another number - stop"  << endl;
        cin >> option;

        switch(option)
        {
        case 1:
            cout << "Enter string to write: " << endl;
            cin >> buffer; 
            cout << "Enter size and position: " << endl;
            cin >> size >> position;
            count = m->write(buffer, size, position);
            for(int i = 0; i < count; ++i)
            {
                cout << buffer[i];
            }
            break;

        case 2:
            cout << "Enter string to write: " << endl;
            cin >> buffer; 
            cout << "Enter size: " << endl;
            cin >> size;
            count = m->write(buffer, size);
            for(int i = 0; i < count; ++i)
            {
                cout << buffer[i];
            }
            break;

        case 3: 
            cout << "Enter size and position: " << endl;
            cin >> size >> position;
            count = m->read(buffer, size, position);
            for(int i = 0; i < count; ++i)
            {
                cout << buffer[i];
            }
            break;

        case 4:
            cout << "Enter size and position: " << endl;
            cin >> size;
            count = m->read(buffer, size);
            for(int i = 0; i < count; ++i)
            {
                cout << buffer[i];
            }
            break;

        case 5:
            cout << "Enter position: " << endl;
            cin >> position;
            try
            {
                m->setCurrPosition(position);
            }
            catch(string e)
            {
                cerr << e << endl;
            }
            break;
        
        default:
            cont = false;
            break;
        }
    }    
}