####### Compiler, tools and options
STRUCT_CC       = gcc
STRUCT_CFLAGS   = -c -g -pipe -O2 -Wall -fPIC
STRUCT_INCPATH  = -I./include

####### Compile rules
all: ../obj/stack.o

../obj/stack.o:
	$(STRUCT_CC) $(STRUCT_CFLAGS) $(STRUCT_INCPATH) -o ../obj/stack.o ./struct/stack.c
