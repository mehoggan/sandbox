LIBS = -lGL -lGLU -lglut

SOURCES = main.cpp camera.cpp moon.cpp ship.cpp torus.cpp

ALL = main.cpp camera.cpp moon.cpp ship.cpp torus.cpp

EXEC = tori

all : $(ALL)

$EXEC : main.cpp camera.cpp moon.cpp ship.cpp torus.cpp
	g++ -o $(EXEC) $(SOURCES) $(LIBS)