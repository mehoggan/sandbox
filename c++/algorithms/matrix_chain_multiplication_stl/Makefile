main : main.o matrix.o
	g++ -Wall -o main main.o matrix.o

matrix.o : matrix.cpp matrix.h
	g++ -c -Wall -o matrix.o matrix.cpp

main.o : main.cpp
	g++ -c -Wall -o main.o main.cpp
