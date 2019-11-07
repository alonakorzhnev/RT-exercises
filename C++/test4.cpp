#include <iostream>

int main()
{
    /*int a = -128;
    char b = a;
    std::cout << (unsigned char)b << std::endl;*/

    char a[] = "111111111111";
    std::cout << a << std::endl;
    *((int*)a+1) = 0;

    return 0;
}