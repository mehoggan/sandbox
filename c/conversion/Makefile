main : reverse.o itoa.o main.o
	ld -o main main.o itoa.o reverse.o

main.o : main.c itoa.o
	$(CC) -o main.o -c main.c

itoa.o : itoa.c reverse.o
	$(CC) -o itoa.o -c itoa.c

reverse.o : reverse.c
	$(CC) -o reverse.o -c reverse.c

clean :
	rm -f *.o
