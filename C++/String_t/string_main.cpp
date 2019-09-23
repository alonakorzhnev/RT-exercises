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

int main()
{
	unsigned int option;
  int cont = 1;
	
	while(cont){
		cout << endl << "Choose option:" << endl;
    cout << "1. Create object with default constructor" << endl;
    cout << "2. Create object with constructor with parameters" << endl;
		cout << "3. Create object with copy constructor" << endl;
    cout << "4. Operator =" << endl;
    cout << "5. String compare" << endl;
    cout << "6. Set string" << endl;
		cout << "Any another number - stop" << endl;
		cin >> option;

		switch(option){
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
  s.print();
}

void paramConstructor()
{
  char* str = new char[MAX_LENGTH];
  cout << "Enter string for constructor: " << endl; 
  cin >> str;
  String_t s(str);
  s.print();
  delete[] str;
}

void copyConstructor()
{
  char* str = new char[MAX_LENGTH];
  cout << "Enter string for constructor for first object: " << endl; 
  cin >> str;
  String_t s1(str);
  s1.print();
  delete[] str;
	String_t s2 = s1;
  s2.print();
}

void operatorAssig()
{
  char* str = new char[MAX_LENGTH];
  cout << "Enter string for constructor for first object: " << endl; 
  cin >> str;
  String_t s1(str);
  s1.print();
  delete[] str;

  cout << "Enter string for constructor for second object: " << endl; 
  cin >> str;
  String_t s2(str);
  s2.print();
  delete[] str;

  s1 = s2;
  s1.print();
}

void stringCompare()
{
  char* str = new char[MAX_LENGTH];
  cout << "Enter string for constructor for first object: " << endl; 
  cin >> str;
  String_t s1(str);
  s1.print();
  delete[] str;

  cout << "Enter string for constructor for second object: " << endl; 
  cin >> str;
  String_t s2(str);
  s2.print();
  delete[] str;

  cout << "Result: " << s1.stringCompare(s2) << endl;
}

void setString()
{
  char* str = new char[MAX_LENGTH];
  cout << "Enter string for constructor for first object: " << endl; 
  cin >> str;
  String_t s1(str);
  s1.print();
  delete[] str;

  cout << "Enter string for set: " << endl; 
  cin >> str; 

  s1.setString(str);
  s1.print();  
}