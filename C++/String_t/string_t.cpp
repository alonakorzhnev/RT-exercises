#include "string_t.h"
#include <string.h>
#define MAX_SIZE 64

char *String_t::createFrom(const char *str)
{
    char *tmp = new char[strlen(str) + 1];
    strcpy(tmp, str);
    return tmp;
}

String_t::String_t()
{
    this->str = createFrom("");
    this->lenght = 0;
}

String_t::String_t(const char *str)
{
    if (str != NULL)
    {
        this->str = createFrom(str);
        this->lenght = strlen(this->str);
    }
}

String_t::String_t(String_t &s)
{
    this->lenght = s.lenght;
    this->str = createFrom(s.str);
}

String_t::~String_t()
{
    delete[] this->str;
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

const int String_t::getLenght() const
{
    return this->lenght;
}

void String_t::setString(const char *str)
{
    if (str != NULL)
    {
        delete[] this->str;
        this->str = createFrom(str);
        this->lenght = strlen(this->str);
    }
}

const char *String_t::getString() const
{
    return this->str;
}

int String_t::stringCompare(const String_t &s) const
{
    int result = strcmp(this->str, s.str);

    if (result < 0)
    {
        return 1;
    }
    else if (result > 0)
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
    cout << "String: " << this->str;
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

void String_t::prepend(const char *str)
{
    char* tmp = new char[strlen(this->str) + strlen(str) + 1];
    strcpy(tmp, str);
    strcat(tmp, this->str);
    delete[] this->str;
    this->str = createFrom(str);
    this->lenght = strlen(this->str);
    delete[] tmp;
}

void String_t::prepend(const String_t &s)
{
    prepend(s.str);
}

String_t& String_t::operator+=(const char *str)
{
    char* tmp = new char[strlen(this->str) + strlen(str) + 1];
    strcpy(tmp, this->str);
    strcat(tmp, str);
    delete[] this->str;
    this->str = createFrom(str);
    this->lenght = strlen(this->str);
    delete[] tmp;
}

String_t& String_t::operator+=(const String_t &s)
{
    return *this += s.str;
}

bool String_t::operator>(const String_t &s)
{
    return (stringCompare(s) == 2) ? true : false;    
}

bool String_t::operator<(const String_t &s)
{
    return (stringCompare(s) == 1) ? true : false;    
}

bool String_t::operator>=(const String_t &s)
{
    return (stringCompare(s) == 2 || stringCompare(s) == 0) ? true : false;    
}

bool String_t::operator<=(const String_t &s)
{
    return (stringCompare(s) == 1 || stringCompare(s) == 0) ? true : false;
}

bool String_t::operator==(const String_t &s)
{
    return (stringCompare(s) == 0) ? true : false;   
}

bool String_t::operator!=(const String_t &s)
{
    return (stringCompare(s) != 0) ? true : false;   
}

bool String_t::contains(const char *str) const
{
    return strstr(this->str, str);
}

char& String_t::operator[](size_t index)
{
    return (index > 0 && index < this->lenght) ? this->str[index] : this->str[this->lenght];
}

char String_t::operator[](size_t index) const
{
    return (index > 0 && index < this->lenght) ? this->str[index] : this->str[this->lenght];    
}

ostream& operator<<(ostream& os, const String_t& s)
{
    os << s.getString();
    return os;
}

istream& operator>>(istream& is, String_t& s)
{
    char str[MAX_SIZE];
    is >> str;
    s.setString(str);
}

