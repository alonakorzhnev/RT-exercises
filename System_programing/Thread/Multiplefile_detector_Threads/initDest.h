#ifndef INIT_H
#define INIT_H

#include "findDup.h"

	int init(ProdSt** prod, ConsSt** const, char* path);
	
	void dest(ProdSt* prod, ConsSt* const);
#endif