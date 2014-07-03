CXXFLAGS = -O2 -g -Wall -fmessage-length=0

OBJS = main.o Daemon.o Tokenizer.o

TARGET = Daemon

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)
	rm *.o

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

	
