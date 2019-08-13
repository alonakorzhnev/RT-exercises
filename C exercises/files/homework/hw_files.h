#ifndef HW_FILES_H
#define HW_FILES_H

struct words
{
    char* word;
    int count;
};

int last(char* fileName, int n);

int countLetters(char* fileName);

int countWords(char* fileName);

#endif