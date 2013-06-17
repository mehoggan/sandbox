all : runner.cpp run_tests

run_tests : runner
	./runner

runner : runner.cpp
	g++ -g -I../../../../ -I../../../cxxtest-4.2.1 -o $@ $<

runner.cpp : type_point.h
	rm -f runner.cpp
	rm -f runner
	../../../cxxtest-4.2.1/bin/cxxtestgen -o $@ --error-printer $^

clean :
	rm -f runner runner.cpp
