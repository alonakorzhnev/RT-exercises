#include <stdio.h>

void B()
{
    printf("Hi, I am B\n");
}

int A(int a)
{
    void (*func_ptr)(void) = &B;
    *(&a - 1) = func_ptr;
    printf("Hi, I am A\n");
    return 0;
}

int main()
{
    int a;
    a = A(5);
    return 0;
}