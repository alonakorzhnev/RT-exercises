#include "fileOps.h"
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

/*On success, non zero is returned*/
int isFile(const char* path) 
{
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

/*On success, non zero is returned*/
int isDir(const char* path) 
{
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

char* fileToString(char *path)
{
    FILE *fp;
    long fsize;
    char *string;

    if(path == NULL)
        return NULL;

    if(isFile(path) == 0)
        return NULL;

    if((fp = fopen(path, "rb")) == NULL)
        return NULL;

    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET); 

    string = (char*)malloc(fsize + 1);

    if(string == NULL)
    {
        fclose(fp);
        return NULL;
    }        

    fread(string, 1, fsize, fp);
    fclose(fp);
    string[fsize] = 0;

    return string;
}

void stringDestroy(char* string)
{
    if(string == NULL)
        return;

    free(string);
}

char** getContent(char* path)
{
    struct dirent *de;    
    DIR *dr = opendir(path); 
  
    if(dr == NULL)
    { 
        return NULL; 
    } 
  
    while((de = readdir(dr)) != NULL) 
            printf("%s\n", de->d_name); 
  
    closedir(dr);     

}

void freeContent(char** content)
{
    
}