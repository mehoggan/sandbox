AR = ar
LD = ld
LL = ls -l
SRC = string.s
OBJ = $(SRC:%.s=%.o)

TARGET = string

all : $(OBJ) $(TARGET)

$(OBJ) : $(SRC)
	as -o $@ $<

$(TARGET) : $(OBJ)
	ld --oformat binary -Tlinker.ld -o $@ $^

install :
	sudo dd if=string of=/dev/sdb
	sudo echo -ne "\x55\xaa" | sudo dd seek=510 bs=1 of=/dev/sdb

clean :
	
	rm -f $(OBJ) $(TARGET)
