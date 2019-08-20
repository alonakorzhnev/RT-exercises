#include <stdio.h>

unsigned int factorial(unsigned int num);

unsigned int factorial(unsigned int num)
{
    if(num == 1)
    {
        return num;
    }
    else
    {
        return factorial(num - 1)*num;
    }

}

int main()
{
    printf("%u\n", factorial(5));
    
    return 0;
}