#ifndef FILEOPS_H
#define FILEOPS_H

int isFile(const char* path);

int isDir(const char* path);

char* fileToString(char* path);

void stringDestroy(char* string);

char** getContent(char* path);

void freeContent(char** content);

#endif