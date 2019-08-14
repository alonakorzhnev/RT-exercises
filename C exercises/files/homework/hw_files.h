#ifndef HW_FILES_H
#define HW_FILES_H

typedef struct word
{
    char word[32];
    int count;
}word;

int last(char* fileName, int n);

int countLetters(char* fileName);

int countWords(char* fileName);

#endif