CFLAGS = -ansi -pedantic -g -Wall 

aprog : main_bst.o bst.o
	gcc -o aprog main_bst.o bst.o -lcunit

main_bst.o : main_bst.c bst.h
	gcc -c $(CFLAFS) main_bst.c

bst.o : bst.c bst.h
	gcc -c $(CFLAGS) bst.c

