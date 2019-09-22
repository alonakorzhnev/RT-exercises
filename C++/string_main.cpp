#include "string_t.h"
#include <iostream>
using namespace std;

int main()
{
	unsigned int option;
	
	while (cont) {
		cout << "Choose option:" << endl;
		
		cout << "Any another number - stop" << endl;

		cin >> option;
		switch (option) {
			case 1:
				
				break;			
				
			default: 
				cont = 0;
				break;
		}

    String_t s1;
    s1.print();
    s1.setString("Alona1");
    s1.print();

    String_t s2("Alona2");
    s2.print();

    String_t s3 = s2;
    s3.print();

    cout << "Result: " << s1.stringCompare(s3) << endl;

    s1 = s2;
    s1.print();

    cout << "Result: " << s1.stringCompare(s3) << endl;

    return 0;
}