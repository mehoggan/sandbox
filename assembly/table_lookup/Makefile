PROG = table_lookup

$(PROG) : $(PROG).asm	
	nasm -f elf -g -F stabs $(PROG).asm
	ld -o $(PROG) $(PROG).o

