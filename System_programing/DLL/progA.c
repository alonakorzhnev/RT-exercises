#include "progB.h"
#include "libN.h"
#include <stdio.h>

void progA()
{
    printf("I am progA\n");
}

int main()
{
    progA();
    progB();
    lib1();
    lib2();
    lib3();

    return 0;
}