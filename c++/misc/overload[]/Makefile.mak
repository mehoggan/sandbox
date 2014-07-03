SOURCE = List[]Operator.cpp
COMPILER = cl.exe
FLAGS = /EHs
DELETE = del

main.exe : $(SOURCE)
	$(COMPILER) $(FLAGS) $(SOURCE)
	$(DELETE) *.obj