####### Global variables
LIB_LINK     = gcc
LIB_AR       = ar cqs
LIB_LFLAGS   = -shared -Wl,-soname,libCalc.so.1
LIB_OBJS     = ../obj/stack.o ../obj/getop.o ../obj/getch.o

####### Include the other make files
all: set_up_build_tree build_components build_lib build_app

set_up_build_tree:
	mkdir -p ../bin
	mkdir -p ../lib
	mkdir -p ../obj

build_components:
	make -f ./input/Makefile
	make -f ./struct/Makefile

build_lib:
	$(LIB_LINK) $(LIB_LFLAGS) $(LIB_OBJS) -o ../lib/libCalc.so.1.0 
	ln -sf libCalc.so.1.0 ../lib/libCalc.so
	ln -sf libCalc.so.1.0 ../lib/libCalc.so.1

build_app:
	make -f ./core/Makefile
	rm -rf ../obj

####### Clean
clean: 
	rm -rf ../bin ../lib ../obj

####### Install
install: FORCE
	test -d $(INSTALL_ROOT)/usr/lib/ || mkdir -p $(INSTALL_ROOT)/usr/lib/ 
	install -m 755 -p "$(TARGET)" "$(INSTALL_ROOT)"
	strip --strip-unneeded "$(INSTALL_ROOT)"

uninstall: uninstall_target FORCE
	rm -f "$(INSTALL_ROOT)" 
