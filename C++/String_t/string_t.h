#ifndef STRING_T
#define STRING_T
#include <iostream>
using namespace std;

class String_t
{
public:
    ~String_t();
    String_t();
    String_t(const char* str);
    String_t(const String_t& s);
    String_t& operator=(const String_t& s);

    int getLenght() const;
    void setString(const char* str);
    const char* getString() const;
    int stringCompare(const String_t& s) const;
    void print() const;

    void toUpper();
    void toLower();

    void prepend(const char* str);
    void prepend(const String_t& s);

    void operator+=(const char* str);
    void operator+=(const String_t& s);

    bool operator>(const String_t& s) const;
    bool operator<(const String_t& s) const;
    bool operator>=(const String_t& s) const;
    bool operator<=(const String_t& s) const;
    bool operator==(const String_t& s) const;
    bool operator!=(const String_t& s) const;

    bool contains(const char* str) const;

    char& operator[](size_t index);
    char operator[](size_t index) const;

private:
    char* str;
    int lenght;
    char* createFrom(const char* str);
    void stringMerge(char* s1, char* s2);
};

ostream& operator<<(ostream& os, const String_t& s);
istream& operator>>(istream& is, String_t& s);

#endif