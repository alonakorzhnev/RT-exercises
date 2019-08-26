CFLAGS = -ansi -pedantic -g 

aprog : main_hashTable.o linkedList.o hashTable.o
	gcc -o aprog main_hashTable.o hashTable.o linkedList.o -lcunit

main_hashTable.o : main_hashTable.c hashTable.h
	gcc -c $(CFLAFS) main_hashTable.c

linkedList.o : linkedList.c linkedList.h
	gcc -c $(CFLAFS) linkedList.c

hashTable.o : hashTable.c hashTable.h
	gcc -c $(CFLAGS) hashTable.c



