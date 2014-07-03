SRC = $(wildcard *.cpp)
OBJS = $(SRC:%.cpp=%.o)
INCLUDE = -I.
LIBS = -lpng
CPPFLAGS += -g -c -Wall
LDFLAGS += $(LIBS)
TARGET = tester
all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJS:%.o) : $(SRC:%.cpp)
	$(CXX) $(CPPFLAGS) -o $@ $<

clean: 
	rm -f $(OBJS) $(TARGET)
