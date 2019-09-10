CFLAGS = -ansi -pedantic -g

aprog : main_ProdCons.o produsers.o consumers.o wQueue.o
	gcc -o aprog main_ProdCons.o produsers.o consumers.o wQueue.o -pthread

main_prodCons.o : main_ProdCons.c produsers.h consumers.h wQueue.h
	gcc -c $(CFLAGS) main_ProdCons.c
	
produsers.o : produsers.c produsers.h wQueue.h
	gcc -c $(CFLAGS) produsers.c

consumers.o : consumers.c consumers.h wQueue.h
	gcc -c $(CFLAFS) consumers.c

wQueue.o : wQueue.c wQueue.h
	gcc -c $(CFLAGS) wQueue.c
