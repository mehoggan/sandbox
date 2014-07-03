####### Compiler, tools and options
LIBC_CC       = gcc
LIBC_LINK     = gcc
LIBC_AR       = ar cqs
LIBC_CFLAGS   = -Wall -fPIC -g -c
LIBC_LFLAGS   = -shared -Wl,-soname,libClib.so.1

####### Build rules
all: ./c_lib/libClib.so.1.0.0 ./c_lib/libClib.a
./c_lib/libClib.so.1.0.0:  ./c_lib/c_lib.o
	$(LIBC_LINK) $(LIBC_LFLAGS) -o ./c_lib/libClib.so.1.0 ./c_lib/c_lib.o 
	ln -sf libClib.so.1.0 ./c_lib/libClib.so
	ln -sf libClib.so.1.0 ./c_lib/libClib.so.1


./c_lib/libClib.a: ./c_lib/c_lib.o
	$(LIBC_AR) ./c_lib/libClib.a ./c_lib/c_lib.o

####### Compile
./c_lib/c_lib.o: ./c_lib/c_lib.c ./c_lib/c_lib.h
	$(LIBC_CC) $(LIBC_CFLAGS) -o ./c_lib/c_lib.o ./c_lib/c_lib.c
