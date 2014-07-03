LIBS = -L/usr/local/boost_1_48_0/stage/lib \
       -lboost_filesystem \
       -lboost_system
INCLUDE = /usr/local/boost_1_48_0/

file_to_map : file_to_map.h main.cpp code_finder.cpp
	g++ -o file_to_map -Wall ./file_to_map.h ./main.cpp ./code_finder.cpp \
        $(LIBS) -I $(INCLUDE)
