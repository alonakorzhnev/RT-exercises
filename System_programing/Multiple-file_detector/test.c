#include "fileOps.h"
#include <stdio.h>

int main()
{
    char* ptr;
    ptr = fileToString("/home/sqrt7/Desktop/sqlink/System_programing/main_pipe.c");
    printf("%s", ptr);
    return 0;
}