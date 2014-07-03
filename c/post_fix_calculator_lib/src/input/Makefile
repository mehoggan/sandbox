####### Compiler, tools and options
INPUT_CC       = gcc
INPUT_LINK     = gcc
INPUT_CFLAGS   = -Wall -g -c -fPIC
INPUT_INCPATH  = -I./include

####### Compile rules
all: input

input: ../obj/getop.o ../obj/getch.o

../obj/getop.o: ./input/getop.c ./include/calc.h
	$(INPUT_CC) $(INPUT_CFLAGS) $(INPUT_INCPATH) -o ../obj/getop.o ./input/getop.c

../obj/getch.o: ./input/getch.c
	$(INPUT_CC) $(INPUT_CFLAGS) $(INPUT_INCPATH) -o ../obj/getch.o ./input/getch.c
