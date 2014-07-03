CXX = g++

CXXFLAGS = -O2 -g -Wall -fmessage-length=0

OBJS = main.o MainWindow.o Controler.o ControlerDrawing.o ModelDrawing.o ViewDrawing.o ControlerChat.o ModelChat.o ViewChat.o ControlerQueue.o ModelQueue.o ViewQueue.o Login_Dialog.o TCP_IP_Socket.o Tutor.o Student.o Tokenizer.o Shape.o Circle.o Square.o Polygon.o Line.o

LIBS1 = `pkg-config --libs gtkmm-2.4`

CXXFLAGS = `pkg-config --cflags gtkmm-2.4`

THREADFLAGS = `pkg-config --libs gthread-2.0`

TARGET = Tutor_App

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAGS) $(LIBS1) $(THREADFLAGS)
	rm *.o

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)


