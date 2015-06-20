.PHONY: all

all:
	g++ -S -std=c++11 -I../ -o main.S main.cpp
	g++ -S -std=c++11 -I../ -o interval.S interval.cpp
	g++ -g -O0 -std=c++11 -I../ -o a.out main.cpp interval.cpp
