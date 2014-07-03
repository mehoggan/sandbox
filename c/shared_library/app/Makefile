####### Compiler, tools and options
APP_CC        = gcc
APP_LINK      = gcc
APP_AR        = ar cqs
APP_CFLAGS    = -g -pipe -O2 -Wall -W -D_REENTRANT
APP_LFLAGS    = -Wl,-O1
APP_INCPATH   = -I./c_lib/
APP_LIBS      = -L./c_lib/ -lClib

####### Build rules
all: ./app/main

./app/main:  ./app/main.o ./c_lib/c_lib.h
	$(APP_LINK) $(APP_LFLAGS) -o ./app/main $(APP_LIBS) ./app/main.o

####### Compile
./app/main.o: ./app/main.c
	$(APP_CC) -c $(APP_CFLAGS) $(APP_INCPATH) -o ./app/main.o ./app/main.c
