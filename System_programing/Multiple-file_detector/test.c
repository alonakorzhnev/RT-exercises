#include "fileOps.h"
#include <stdio.h>

int main()
{
    char **content;
    int index = 0; 

    content = getContent("/home/sqrt7/Desktop/sqlink/System_programing/");

    while(content[index] != NULL)
    {
        printf("%s\n", content[index]);
        printf("%d\n", isFile(content[index]));
        ++index;
    }

    freeContent(content);

    return 0;
}