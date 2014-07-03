main: libmyclass.so main.o
	$(CXX) -o main  main.o -L. -lmyclass
	export LD_LIBRARY_PATH=.
	./main

libmyclass.so: myclass.cpp
	$(CXX) -fPIC -c myclass.cpp -o myclass.o
	$(CXX) -o libmyclass.so -shared  -Wl,-soname,libmyclass.so myclass.o

clean:
	rm *.o *.so
