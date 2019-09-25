#include "string_t.h"
#include <string.h>
#include <math.h>
#define MAX_LEN 64

int String_t::capacityDef = 8;
bool String_t::caseSens = true;
size_t String_t::stringCount = 0;

char *String_t::createFrom(const char* s)
{
    if((strlen(s) + 1) <= this->capacity)
    {
        strcpy(this->str, s);        
    }
    else
    {
        size_t size = pow(2, ceil(log2(strlen(s) + 1)));
        char *tmp = new char[size];
        strcpy(tmp, s);
        this->capacity = size;
        return tmp;
    }
}

void String_t::stringMerge(char* s1, char* s2)
{
    char* tmp = new char[strlen(s1) + strlen(s2) + 1];
    strcpy(tmp, s1);
    strcat(tmp, s2);
    delete[] this->str;
    this->str = tmp;
    this->lenght = strlen(this->str);
}

String_t::String_t()
{
    this->lenght = 0;
    this->capacity = capacityDef;
    this->str = new char[capacityDef];
    this->stringCount++;
}

String_t::String_t(const char* s)
{    
    size_t size = pow(2, ceil(log2(strlen(s) + 1)));
    char *tmp = new char[size];
    strcpy(tmp, s);
    this->str = tmp;
    this->capacity = size;
    this->lenght = strlen(this->str);
    this->stringCount++;
}

String_t::String_t(const String_t& s)
{
    this->str = createFrom(s.str);
    this->lenght = s.lenght;
    this->stringCount++;
}

String_t::~String_t()
{
    delete[] this->str;
    this->stringCount--;
}

String_t &String_t::operator=(const String_t &s)
{
    if (this != &s)
    {
        delete[] this->str;
        this->str = createFrom(s.str);
    }
    return *this;
}

int String_t::getLenght() const
{
    return this->lenght;
}

void String_t::setString(const char* s)
{
    if (s != NULL)
    {
        delete[] this->str;
        this->str = createFrom(s);
        this->lenght = strlen(this->str);
    }
}

const char *String_t::getString() const
{
    return this->str;
}

int String_t::stringCompare(const String_t &s) const
{
    if(caseSens)
    {
        int result = strcmp(this->str, s.str);
        return (result == 0) ? 0 : (result < 0) ? 1 : 2;
    }
    else
    {
        int result = strcasecmp(this->str, s.str);
        return (result == 0) ? 0 : (result < 0) ? 1 : 2;
    }    
}

void String_t::print() const
{
    cout << this->str;
}

void String_t::toUpper()
{
    for (int i = 0; i < this->lenght; ++i)
    {
        this->str[i] = toupper(this->str[i]);
    }
}

void String_t::toLower()
{
    for (int i = 0; i < this->lenght; ++i)
    {
        this->str[i] = tolower(this->str[i]);
    }
}

void String_t::prepend(const char* s)
{
    stringMerge((char*)s, this->str);
}

void String_t::prepend(const String_t& s)
{
    stringMerge(s.str, this->str);
}

void String_t::operator+=(const char* s)
{
    stringMerge(this->str, (char*)s);
}

void String_t::operator+=(const String_t& s)
{
    stringMerge(this->str, s.str);
}

bool String_t::operator>(const String_t& s) const
{
    return (stringCompare(s) == 2) ? true : false;    
}

bool String_t::operator<(const String_t& s) const
{
    return (stringCompare(s) == 1) ? true : false;    
}

bool String_t::operator>=(const String_t& s) const
{
    return (stringCompare(s) == 2 || stringCompare(s) == 0) ? true : false;    
}

bool String_t::operator<=(const String_t& s) const
{
    return (stringCompare(s) == 1 || stringCompare(s) == 0) ? true : false;
}

bool String_t::operator==(const String_t& s) const
{
    return (stringCompare(s) == 0) ? true : false;   
}

bool String_t::operator!=(const String_t& s) const
{
    return (stringCompare(s) != 0) ? true : false;   
}

bool String_t::contains(const char* str) const
{
    return strstr(this->str, str);
}

char& String_t::operator[](size_t index)
{
    return (index < this->lenght) ? this->str[index] : this->str[this->lenght];
}

char String_t::operator[](size_t index) const
{
    return (index < this->lenght) ? this->str[index] : this->str[this->lenght];    
}

ostream& operator<<(ostream& os, const String_t& s)
{
    os << s.getString();
    return os;
}

istream& operator>>(istream& is, String_t& s)
{
    char str[MAX_LEN];
    is >> str;
    s.setString(str);
}

int String_t::getFirstIndex(char ch) const
{
    for(int i = 0; i < this->lenght; i++)
    {
        if(this->str[i] == ch)
        {
            return i;
        }
    }
    return -1;
}

int String_t::getLastIndex(char ch) const
{
    int index = -1;
    for(int i = 0; i < this->lenght; i++)
    {
        if(this->str[i] == ch)
        {
            index = i;
        }
    }
    return index;
}

String_t String_t::operator()(size_t start, size_t len) const
{
    String_t s;
    if(start < this->lenght)
    {
        char* tmp = new char[this->lenght];
        strncpy(tmp, this->str + start, len);
        s.setString(tmp);
        delete[] tmp;
    }
    return s;
}

