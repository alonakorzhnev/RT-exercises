#ifndef BITOP_H
#define BITOP_H

unsigned char bitInvers(unsigned char n);

void char2Bin(char c);

unsigned char bitRotate(unsigned char n, int steps);

unsigned char setBitsFirst(unsigned char x, int p, int n, unsigned char y);

unsigned int setBitsSecond(unsigned int w, int i, int j, int value);

void int2Bin(int num);

#endif