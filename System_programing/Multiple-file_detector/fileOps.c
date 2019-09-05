#include "fileOps.h"
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int countContent(char* path)
{
    struct dirent *de;    
    DIR *dr;
    int count = 0;

    if(path == NULL)
    {
        return 0;
    }

    dr = opendir(path);   
    if(dr == NULL)
    { 
        return 0; 
    } 
  
    while((de = readdir(dr)) != NULL) 
    {
        if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) 
            continue;
        ++count;
    }
    closedir(dr);
    return count;
}

char** getContent(char* path)
{
    struct dirent *de;    
    DIR *dr;
    char **content;
    char *buffer;
    int count = countContent(path), index = 0;

    dr = opendir(path);   
    if(dr == NULL)
    { 
        return NULL; 
    }

    content = (char**)malloc((count + 1)*sizeof(char*));

    if(content == NULL)
    {
        closedir(dr);
        return NULL;
    }

    while((de = readdir(dr)) != NULL) 
    {
        if(strcmp(de->d_name,".")==0 || strcmp(de->d_name,"..")==0) 
            continue;        
        buffer = (char*)malloc(512*sizeof(char));
        strcpy(buffer, path); 
        strcat(buffer, "/");
        strcat(buffer, de->d_name);   
        content[index] = buffer;                             
        ++index;
    }
    content[index] = NULL;
  
    closedir(dr); 
    return content;   
}

void freeContent(char** content)
{
    int index = 0; 

    if(content == NULL)
    {
        return;
    } 

    while(content[index] != NULL)
    {
        free(content[index]);
        ++index;
    }
    free(content);
}