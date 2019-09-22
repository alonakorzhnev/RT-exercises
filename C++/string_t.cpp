#include "string_t.h"
#include <string.h>
#include <iostream>
using namespace std;

char* String_t::createFrom(const char* str)
{
    char* tmp = new char[strlen(str) + 1];
    strcpy(tmp, str);
    return tmp;
}

String_t::String_t()
{
    this->str = 0;
    this->lenght = 0;
}

String_t::String_t(const char* str)
{
    if(str != NULL)
    {
        this->str = createFrom(str);
        this->lenght = strlen(this->str);
    }
}

String_t::String_t(String_t& s)
{
    this->lenght = s.lenght;
    this->str = createFrom(s.str);
}

String_t::~String_t()
{
    delete[] this->str;
}

String_t& String_t::operator=(const String_t& s)
{
    if(this != &s)
    {
        delete[] this->str;
        this->str = createFrom(s.str);
    }
    return *this;
}

const int String_t::getLenght() const
{
    return this->lenght;
}

void String_t::setString(const char* str)
{
     if(str != NULL)
    {
        delete[] this->str;
        this->str = createFrom(str);
        this->lenght = strlen(this->str);
    }
}

const char* String_t::getString() const
{
    return this->str;
}

int String_t::stringCompare(const String_t& s) const
{
    int result = strcmp(this->str, s.str);

    if(result < 0)
    {
        return 1;
    }
    else if(result > 0)
    {
        return 2;
    }
    else
    {
        return 0;
    }    
}

void String_t::print() const
{
    if(this->str != NULL)
    {
        cout << "String: ";
        for(int i = 0; i < this->lenght; i++)
        {
        cout << this->str[i];
        }
    }
    else
    {
        cout << "String: NULL";
    }
    
    cout << " lenght: " << this->lenght << endl;
}
