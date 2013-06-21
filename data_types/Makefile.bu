all : a.out

asm : a.S

a.out : main.o

a.S : main.cpp
	g++ -O3 -S -pedantic -Wall -I./ main.cpp

main.o : main.cpp
	g++ -O3 -pedantic -Wall -I./ main.cpp

clean :
	rm -f main.o a.out main.s
