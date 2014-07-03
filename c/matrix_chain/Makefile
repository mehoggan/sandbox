ASSEMBLY = -S

main : main.o matrix_list.o matrix.o
	gcc -g -o main main.o matrix_list.o matrix.o
	rm -f *.o

main.o : main.c
	gcc -g -c main.c

matrix_list.o : matrix_list.h matrix_list.c
	gcc -g -c matrix_list.c

matrix.o : matrix.h matrix.c
	gcc -g -c matrix.c
