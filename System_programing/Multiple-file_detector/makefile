CFLAGS = -ansi -pedantic -g

aprog : findDup.o linkedList.o hashTable.o fileOps.o md5.o initDest.o
	gcc -o aprog findDup.o hashTable.o linkedList.o fileOps.o md5.o initDest.o -lcrypto

findDup.o : findDup.c findDup.h fileOps.h md5.h hashTable.h initDest.h
	gcc -c $(CFLAGS) findDup.c findDup.h fileOps.h md5.h hashTable.h initDest.h

fileOps.o : fileOps.c fileOps.h
	gcc -c $(CFLAGS) fileOps.c

initDest.o : initDest.c initDest.h fileOps.h
	gcc -c $(CFLAFS) initDest.c

md5.o : md5.c md5.h
	gcc -c $(CFLAFS) md5.c

linkedList.o : linkedList.c linkedList.h
	gcc -c $(CFLAFS) linkedList.c

hashTable.o : hashTable.c hashTable.h linkedList.h
	gcc -c $(CFLAGS) hashTable.c