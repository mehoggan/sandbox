all : a.out

a.out : main.o

main.o : main.cpp
	g++ -pedantic -Wall -I./ main.cpp

clean :
	rm -f main.o a.out
