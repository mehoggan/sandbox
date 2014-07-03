AR = ar
LD = ld
LL = ls -l
SRC = putstring.s
OBJ = $(SRC:%.s=%.o)

TARGET = putstring

all : $(OBJ) $(TARGET)

$(OBJ) : $(SRC)
	as -o $@ $<

$(TARGET) : $(OBJ)
	ld --oformat binary -Tlinker.ld -o $@ $^

install :
	sudo dd if=$(TARGET) of=/dev/sdb

clean :
	
	rm -f $(OBJ) $(TARGET)
