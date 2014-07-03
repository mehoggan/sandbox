all : linux_main

linux_main : map.o linux_main.o
	g++ -pthread -Wall linux_main.o map.o -o linux_main -lGL -lXext -lX11 -lGLU -lXmu

linux_main.o : linux_main.cpp
	g++ -pthread -Wall -c -o linux_main.o linux_main.cpp

map.o : map.cpp
	g++ -pthread -Wall -c -o map.o map.cpp

clean :
	rm -f ./*.o linux_main
