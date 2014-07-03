AR = ar
LD = ld
LL = ls -l
SRC = putstring.s
OBJ = $(SRC:%.s=%.o)
FILE = $(shell findfs LABEL=SEGATEUSB)

TARGET = putstring

all : $(OBJ) $(TARGET)

$(OBJ) : $(SRC)
	as -o $@ $<

$(TARGET) : $(OBJ)
	ld --oformat binary -Tlinker.ld -o $@ $^

install :
	sudo dd if=$(TARGET) of=$(FILE)

clean :
	rm -f $(OBJ) $(TARGET)
