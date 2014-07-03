testlib : testlib.o
	gcc -o testlib testlib.o -L. -lcomplex
	# Note comlex does not have lib--.a on it
	# Note -L. contains

libtest.o : testlib.c
	gcc -c testlib.c

complex.o : complex.c
	gcc -o complex.o -c complex.c
	ar -q libcomplex.a complex.o
