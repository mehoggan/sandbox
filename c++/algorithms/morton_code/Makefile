.PHONY : all clean

OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all : a.out

a.out : $(OBJECTS)
	$(CXX) -o a.out $(OBJECTS)

%.o : %.cpp
	$(CXX) -g -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean :
	$(RM) a.out $(OBJECTS)
