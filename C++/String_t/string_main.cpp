#include "string_t.h"
#include <iostream>
#define MAX_LENGTH 64
using namespace std;

void defaultConstructor();
void paramConstructor();
void copyConstructor();
void operatorAssig();
void stringCompare();
void setString();
void toUpper();
void toLower();
void prependObj();
void prependStr();
void plusAssObj();
void plusAssStr();
void boolOperators();
void strContain();
void getChar();
void setChar();

int main()
{
  unsigned int option;
  int cont = 1;

  while (cont)
  {
    cout << endl
         << "Choose option:" << endl
         << "1. Create object with default constructor" << endl
         << "2. Create object with constructor with parameters" << endl
         << "3. Create object with copy constructor" << endl
         << "4. Operator =" << endl
         << "5. String compare" << endl
         << "6. Set string" << endl
         << "7. To upper case" << endl
         << "8. To lower case" << endl
         << "9. Prepend with object" << endl
         << "10. Prepend with string" << endl
         << "11. Operator += with object" << endl
         << "12. Operator += with string" << endl
         << "13. Boolean operators" << endl
         << "14. String contains" << endl
         << "15. Get char by index" << endl
         << "16. Change char by index" << endl
         << "Any another number - stop" << endl;
    cin >> option;

    switch (option)
    {
    case 1:
    {
      defaultConstructor();
      break;
    }
    case 2:
    {
      paramConstructor();
      break;
    }
    case 3:
    {
      copyConstructor();
      break;
    }
    case 4:
    {
      operatorAssig();
      break;
    }
    case 5:
    {
      stringCompare();
      break;
    }
    case 6:
    {
      setString();
      break;
    }
    case 7:
    {
      toUpper();
      break;
    }
    case 8:
    {
      toLower();
    }
    case 9:
    {
      prependObj();
      break;
    }
    case 10:
    {
      prependStr();
      break;
    }
    case 11:
    {
      plusAssObj();
      break;
    }
    case 12:
    {
      plusAssStr();
      break;
    }
    case 13:
    {
      boolOperators();
      break;
    }
    case 14:
    {
      strContain();
      break;
    }
    case 15:
    {
      getChar();
      break;
    }
    case 16:
    {
      setChar();
      break;
    }
    default:
    {
      cont = 0;
      break;
    }
    }
  }
  return 0;
}

void defaultConstructor()
{
  String_t s;
  cout << "String: " << s << endl;
}

void paramConstructor()
{
  char *str = new char[MAX_LENGTH];
  cout << "Enter string for constructor: " << endl;
  cin >> str;
  String_t s(str);
  cout << "String: " << s << endl;
  delete[] str;
}

void copyConstructor()
{
  char *str = new char[MAX_LENGTH];
  cout << "Enter string for constructor for first object: " << endl;
  cin >> str;
  String_t s1(str);
  cout << "String: " << s1 << endl;
  delete[] str;
  String_t s2 = s1;
  cout << "String: " << s2 << endl;
}

void operatorAssig()
{
  char *str = new char[MAX_LENGTH];
  cout << "Enter string for constructor for first object: " << endl;
  cin >> str;
  String_t s1(str);
  cout << "String: " << s1 << endl;

  cout << "Enter string for constructor for second object: " << endl;
  cin >> str;
  String_t s2(str);
  cout << "String: " << s2 << endl;
  delete[] str;

  s1 = s2;
  cout << "String: " << s1 << endl;
}

void stringCompare()
{
  char *str = new char[MAX_LENGTH];
  cout << "Enter string for constructor for first object: " << endl;
  cin >> str;
  String_t s1(str);
  cout << "String: " << s1 << endl;

  cout << "Enter string for constructor for second object: " << endl;
  cin >> str;
  String_t s2(str);
  cout << "String: " << s2 << endl;
  delete[] str;

  cout << "Result: " << s1.stringCompare(s2) << endl;
}

void setString()
{
  char *str = new char[MAX_LENGTH];
  cout << "Enter string for constructor for first object: " << endl;
  cin >> str;
  String_t s1(str);
  cout << "String: " << s1 << endl;
  delete[] str;

  cout << "Enter string for set: " << endl;
  cin >> str;

  s1.setString(str);
  cout << "String: " << s1 << endl;
}

void toUpper()
{
  char str[MAX_LENGTH];
  cout << "Enter string to convert to upper case: " << endl;
  cin >> str;
  String_t s(str);
  cout << "String: " << s << endl;
  s.toUpper();
  cout << "Result: " << s << endl;
}

void toLower()
{
  char str[MAX_LENGTH];
  cout << "Enter string to convert to lower case: " << endl;
  cin >> str;
  String_t s(str);
  cout << "String: " << s << endl;
  s.toLower();
  cout << "Result: " << s << endl;
}

void prependObj()
{
  char str[MAX_LENGTH];
  cout << "Enter string to create first object: " << endl;
  cin >> str;
  String_t s1(str);
  cout << "String 1: " << s1 << endl;

  cout << "Enter string to create second object: " << endl;
  cin >> str;
  String_t s2(str);
  cout << "String 2: " << s2 << endl;

  s1.prepend(s2);
  cout << "Result of string 1: " << s1 << endl;
}

void prependStr()
{
  char str[MAX_LENGTH];
  cout << "Enter string to create object: " << endl;
  cin >> str;
  String_t s(str);
  cout << "String: " << s << endl;

  cout << "Enter string to prepend to object: " << endl;
  cin >> str;

  s.prepend(str);
  cout << "Result of string: " << s << endl;
}

void plusAssObj()
{
  char str[MAX_LENGTH];
  cout << "Enter string to create first object: " << endl;
  cin >> str;
  String_t s1(str);
  cout << "String 1: " << s1 << endl;

  cout << "Enter string to create second object: " << endl;
  cin >> str;
  String_t s2(str);
  cout << "String 2: " << s2 << endl;

  s1 += s2;
  cout << "Result of string 1: " << s1 << endl;
}

void plusAssStr()
{
  char str[MAX_LENGTH];
  cout << "Enter string to create object: " << endl;
  cin >> str;
  String_t s(str);
  cout << "String: " << s << endl;

  cout << "Enter string to append to object: " << endl;
  cin >> str;

  s += str;
  cout << "Result of string: " << s << endl;
}

void boolOperators()
{
}

void strContain()
{
  char str[MAX_LENGTH];
  cout << "Enter string to create object: " << endl;
  cin >> str;
  String_t s(str);
  cout << "String: " << s << endl;

  cout << "Enter string to find if object contains it: " << endl;
  cin >> str;
  cout << "Result: " << s.contains(str) << endl;
}

void getChar()
{
  char str[MAX_LENGTH];
  cout << "Enter string to create object: " << endl;
  cin >> str;
  String_t s(str);
  cout << "String: " << s << endl;

  int index;
  cout << "Enter index of char: " << endl;
  cin >> index;
  cout << "Result: " << s[index] << endl;
}

void setChar()
{
  char str[MAX_LENGTH];
  cout << "Enter string to create object: " << endl;
  cin >> str;
  String_t s(str);
  cout << "String: " << s << endl;

  int index;
  char ch;
  cout << "Enter index of char and char to set: " << endl;
  cin >> index >> ch;
  s[index] = ch;
  cout << "Result: " << s << endl;
}