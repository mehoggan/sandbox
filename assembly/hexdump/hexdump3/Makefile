PROG = hexdump3
LIB = textlib

all : $(LIB) $(PROG)

$(LIB) : $(LIB).asm
	nasm -f elf -g -F stabs $(LIB).asm

$(PROG) : $(PROG).asm	
	nasm -f elf -g -F stabs $(PROG).asm
	ld -o $(PROG) $(PROG).o $(LIB).o

