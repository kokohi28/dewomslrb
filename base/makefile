#. resources
# Files:	Tools.h			: Standard utility tools
# 			TcpHandler.h	: Network TCP utiliy (RefBox Purpose)
# 			UdpHandler.h	: Network UDP utiliy (Robo Purpose)
#			ConfigParser.h	: Program Config Parser module
# 			Dewo.h		: Main program

HEADERS		= Tools.h TcpHandler.h UdpHandler.h ConfigParser.h
OBJECTS		= Tools.o TcpHandler.o UdpHandler.o ConfigParser.o
TARGET_O	= Dewo.o
TARGET		= Dewo

#. flag used
CFLAGS		= -c

#. additional libs
LIBS		= -lm -lpthread

#. rule used
all: $(TARGET)

$(OBJECTS) $(TARGET_O) : $(HEADERS)

$(TARGET): $(OBJECTS) $(TARGET_O)
	$(CXX) -o $@ $^ $(LIBS)

#. clean command
clean:
	rm -f *o $(TARGET)
