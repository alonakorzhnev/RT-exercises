CFLAGS = -ansi -pedantic -g

aprog : darray_test.o darray_generic.o
	gcc -o aprog darray_test.o darray_generic.o -lm

darray_test.o : darray_test.c darray_generic.h
	gcc -c $(CFLAFS) darray_test.c

darray_int.o : darray_generic.c darray_generic.h
	gcc -c $(CFLAGS) darray_generic.c

