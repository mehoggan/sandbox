CXXFLAGS += -Wall -O2
TARGET = bool_analyzer
SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=%.o)

all : clean $(TARGET) $(OBJ)

$(TARGET) : $(OBJ)
	$(CXX) -o $(TARGET) $^
	rm -rf *.o

%.obj : %.cpp
	g++ -o $@ $(CXXFLAGS) $<

clean :
	rm -f *.o
