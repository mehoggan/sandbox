####### Compiler, tools and options
CORE_CC        = gcc
CORE_LINK      = gcc
CORE_AR        = ar cqs
CORE_CFLAGS    = -c -g -pipe -O2 -Wall
CORE_LFLAGS    = -Wl,-O1
CORE_INCPATH   = -I./include/
CORE_LIBS      = -L../lib/ -lCalc
CORE_OBJS      = ../obj/main.o

####### Build rules
all: ../bin/main

####### Link rules
../bin/main:  ../obj/main.o ./include/calc.h
	$(CORE_LINK) $(CORE_LFLAGS) -o ../bin/main $(CORE_LIBS) $(CORE_OBJS)

####### Compile
../obj/main.o: ./core/main.c
	$(CORE_CC) $(CORE_CFLAGS) $(CORE_INCPATH) -o ../obj/main.o ./core/main.c
