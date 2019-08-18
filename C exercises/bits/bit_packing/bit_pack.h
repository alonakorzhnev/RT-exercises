#ifndef BIT_PACK_H
#define BIT_PACK_H

typedef struct
{		
		unsigned int m_right	:4;
		unsigned int m_left		:4;
} Pack;

union un
{
	Pack charPack;
	char c;
};

int withoutBitField(char* string);

int withBitField(char* string);

void printBits(char* string, int size);

#endif