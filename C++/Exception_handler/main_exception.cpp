#include "exception_t.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
    try
    {
        throw TException_t<string>("Error 123", "Division by zero", __FILE__, __LINE__);
    }
    catch (const TException_t<string> &e)
    {
        cerr <<     e.getException()    << endl
             <<     e.getMessage()      << endl
             <<     e.getFileName()     << endl
             <<     e.getLineNumber()   << endl;
    }

    try
    {
        throw TException_t<int>(876, "NULL pointer", __FILE__, __LINE__);
    }
    catch (const TException_t<int> &e)
    {
        cerr <<     e.getException()    << endl
             <<     e.getMessage()      << endl
             <<     e.getFileName()     << endl
             <<     e.getLineNumber()   << endl;
    }

    return 0;
}