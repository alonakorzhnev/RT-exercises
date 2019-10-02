#include "memPage_t.h"
#include "memPool_t.h"
#include <iostream>

using namespace std;

int main()
{
    /*MemPage_t mp(16);

    char* data1 = "Hello world";
    char* data2 = "!!???";
    char buffer[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    size_t count;

    count = mp.write(data1, 11);
    cout << count << endl;

    count = mp.write(data2, 5);
    cout << count << endl;

    count = mp.read(buffer, 16);
    cout << count << endl;

    cout << buffer << endl;*/

    MemPool_t mp;

    char* data1 = "Hello world!!!";
    char* data2 = "New!!???";
    char buffer[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    size_t count;

    count = mp.write(data1, 14);
    cout << count << endl;

    count = mp.read(buffer, 16, 0);
    cout << count << endl;

    cout << buffer << endl;

    count = mp.write(data2, 7);
    cout << count << endl;

    count = mp.read(buffer, 32, 0);
    cout << count << endl;

    cout << buffer << endl;

    return 0;
}