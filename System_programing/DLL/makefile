doall : prog libN.so

prog : progA.o progB.o libN.so
	gcc -o prog progA.o progB.o -lN -L.

progA.o : progA.c progB.h
	gcc -c progA.c progB.h

progB.o : progB.c progB.h
	gcc -c progB.c progB.h

libN.so : lib1.o lib2.o lib3.o
	gcc -o libN.so -shared lib1.o lib2.o lib3.o

lib1.o : lib1.c libN.h
	gcc -c -fPIC lib1.c libN.h

lib2.o : lib2.c libN.h
	gcc -c -fPIC lib2.c libN.h

lib3.o : lib3.c libN.h
	gcc -c -fPIC lib3.c libN.h