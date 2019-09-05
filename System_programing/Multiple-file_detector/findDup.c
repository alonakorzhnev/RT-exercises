#include "findDup.h"
#include "fileOps.h"
#include "md5.h"
#include "hashTable.h"
#include "initDest.h"
#include <stdlib.h>
#include <stdio.h>

static void fileScan(char* path, HashTable* hashTable)
{
    char **content;
    int index = 0;
    unsigned char* md5Out;
    int status;
    void *voidPtr;

    content = getContent(path);

    while(content[index] != NULL)
    {        
        if(isFile(content[index]))
        {
            md5Out = file2md5(content[index]);
            status = hashTableInsert(hashTable, md5Out, content[index]);
            if(status != 0)
            {                
                if(status == 4)
                {
                    hashTableFind(hashTable, md5Out, &voidPtr);
                    printf("File %s already exist in %s\n", content[index], (char*)voidPtr);
                }
                free(md5Out);
                free(content[index]);
            }
        }
        else if(isDir(content[index]))
        {
            fileScan(content[index], hashTable);
            free(content[index]);
        }
        ++index;
    }
}

void findDup(char* path)
{
    HashTable *hashTable;

    hashTable = init(path);

    if(hashTable == NULL)
    {
        return;
    }

    fileScan(path, hashTable);

    dest(hashTable);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
        return 1;

    findDup(argv[1]);
    return 0;
}