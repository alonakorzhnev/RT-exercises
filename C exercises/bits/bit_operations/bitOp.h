#ifndef BITOP_H
#define BITOP_H

unsigned char bitInvers(unsigned char n);

void char2Bin(char c);

unsigned char bitRotate(unsigned char n, int steps);

unsigned char setBits1(unsigned char x, int p, int n, unsigned char y);

unsigned char setBits2(unsigned int w, int i, int j, int value);

#endif