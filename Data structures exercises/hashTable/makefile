CFLAGS = -ansi -pedantic -g -Wall 

aprog : main_hashTable.o hashTable.o
	gcc -o aprog main_hashTable.o hashTable.o -lcunit

main_hashTable.o : main_hashTable.c hashTable.h
	gcc -c $(CFLAFS) main_hashTable.c

hashTable.o : hashTable.c hashTable.h
	gcc -c $(CFLAGS) hashTable.c

