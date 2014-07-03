CC = /usr/bin/gcc
LD = /usr/bin/gcc
CFLAGS = -c -Wall -g
LDFLAGS = -Wl,-rpath=./ -L./ -lpng12
INCLUDE = -I/usr/include/libpng

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

TARGET = progressive

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(LD) $^ $(LDFLAGS) -o $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $<

clean :
	rm -rf *.o $(TARGET)

