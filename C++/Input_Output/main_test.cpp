#include "binIO_t.h"
#include "asciiIO_t.h"
#include "virtIO_t.h"
#include <iostream>
#include <string>

using namespace std;

template <class T> void writeTempl(VirtIO_t* filePtr, T val);
template <class T> void readTempl(VirtIO_t* filePtr, T val);

void writeVoidPtr(VirtIO_t* filePtr);

void test(char type);
void writeToFile(VirtIO_t* filePtr);
void readFromFile(VirtIO_t* filePtr);

int main()
{   
    char type;

    while(true)
    {
        cout << endl << "Choose type o file Binary/Ascii: [b/a] ";
        cin >> type;

        if(type == 'b' || type == 'a')
        {
            test(type);
        }
        else break;
    }
  
    return 0;
}

void test(char type)
{
    VirtIO_t* filePtr = 0;
    string name, access;

    cout << "Enter name of file and access mode: ";
    cin >> name >> access;

    if(type == 'b')
    {
        filePtr = new BinIO_t(name, access);
    }
    else
    {
        filePtr = new AsciiIO_t(name, access);
    }

    bool cond = true;

    while(cond)
    {
        size_t option;
        cout << "Choose option with file: "     << endl
             << "1. Operator <<"                << endl
             << "2. Operator >>"                << endl
             << "3. Get lenght"                 << endl
             << "4. Set position"               << endl
             << "5. Get position"               << endl
             << "Any another number - break"    << endl;
        cin >> option;

        switch(option)
        {
            case 1:
                writeToFile(filePtr);
                break;
            case 2:
                readFromFile(filePtr);
                break;
            case 3:
                cout << "Lenght: " << filePtr->getFileLenght() << endl;
                break;
            case 4:
                size_t position;
                cout << "Enter position: ";
                cin >> position;
                filePtr->setPosition(position);
                break;            
            case 5:
                cout << "Position: " << filePtr->getPosition() << endl;
                break;
            default:
                cond = false;
                break;
        }
    }
    delete filePtr;
}

template <class T> void writeTempl(VirtIO_t* filePtr, T val)
{
    try
    {
        filePtr->open();
        filePtr->operator<<(val);
    }
    catch(string e)
    {
        cout << e << endl;
    }
    filePtr->close();
}

template <class T> void readTempl(VirtIO_t* filePtr, T val)
{
    try
    {
        filePtr->open();
        filePtr->operator>>(val);
    }
    catch(string e)
    {
        cout << e << endl;
    }
    filePtr->close();
}

void writeToFile(VirtIO_t* filePtr)
{
    char type;
    cout << "Enter type of value int(i)/float(f)/void*(v): ";
    cin >> type;

    switch(type)
    {
        case 'i':
        {
            int val;
            cout << "Enter int value: ";
            cin >> val;
            writeTempl<int>(filePtr, val);
            break;
        }
        case 'f':
        {
            float val;
            cout << "Enter float value: ";
            cin >> val;
            writeTempl<float>(filePtr, val);
            break;
        }
        case 'v':
        {
            if(BinIO_t* fileBin = dynamic_cast<BinIO_t*>(filePtr))
            {
                writeVoidPtr(filePtr);
            }
            break;
        }        
        default:
            break;
    }
}

void readFromFile(VirtIO_t* filePtr)
{
    
}

void writeVoidPtr(VirtIO_t* filePtr)
{
    double val;

    cout << "Enter value double: ";
    cin >> val;

    try
    {
        /* code */
    }
    catch(string e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
