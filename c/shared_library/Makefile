####### Implicit rules
.SUFFIXES: .o .c

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Include the other make files
all: 

include ./c_lib/Makefile ./app/Makefile

####### Clean
clean: 
	rm -f ./c_lib/libClib.so.1.0.0 ./c_lib/libClib.so ./c_lib/libClib.so.1 \
	./c_lib/libClib.so.1.0 ./c_lib/libClib.a ./c_lib/*.o
	rm -f ./app/*.o ./app/main

####### Install
#install: FORCE
#	test -d $(INSTALL_ROOT)/usr/lib/ || mkdir -p $(INSTALL_ROOT)/usr/lib/ 
#	install -m 755 -p "$(TARGET)" "$(INSTALL_ROOT)/usr/lib/libClib.so.1.0.0"
#	strip --strip-unneeded "$(INSTALL_ROOT)/usr/lib/libClib.so.1.0.0"

#uninstall: uninstall_target FORCE
#	rm -f "$(INSTALL_ROOT)/usr/lib/libClib.so" 
#	rm -f "$(INSTALL_ROOT)/usr/lib/libClib.so.1" 
#	rm -f "$(INSTALL_ROOT)/usr/lib/libClib.so.1.0"
#	rm -f "$(INSTALL_ROOT)/usr/lib/libClib.so.1.0.0" 
