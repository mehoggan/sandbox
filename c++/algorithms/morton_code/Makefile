OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all : a.out

a.out : $(OBJECTS)
	$(CXX) -o a.out $(OBJECTS)

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
