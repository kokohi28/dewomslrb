#. resources
# Files:	Tools.h			: Standard utility tools
# 			Vision.h		: OpenCV, Camera module
#			Uart.h			: Standart UART Comm module
#			I2CDev.h		: I2C Pi Interface
#			CMPS10.h		: CMPS10 Compass sensor module
#			BMP085.h		: BMP085 Pressure sensor module
#			MPU6050.h		: MPU6050 6-Axis Motion sensor module
#			HMC5883L.h		: HMC5883L Digital Compass sensor module
#			ConfigParser.h	: Program Config Parser module
# 			UdpHandler.h	: Network UDP utiliy (Robo Purpose)
# 			Dewo.h			: Main program

#. All HEADERS		= Tools.h Vision.h Uart.h ConfigParser.h I2CDev.h CMPS10.h BMP085.h MPU6050.h UdpHandler.h HMC5883L.h
HEADERS		= Tools.h Vision.h Uart.h ConfigParser.h UdpHandler.h
OBJECTS		= Tools.o Vision.o Uart.o ConfigParser.o UdpHandler.o
TARGET_O	= Dewo.o
TARGET		= Dewo

#. flag used
CFLAGS		= -c
CFLAGS_CV	= $(CFLAGS) `pkg-config --cflags opencv`

#. additional libs
LIBS		= -lm -lpthread
LIBS_CV		= $(LIBS) `pkg-config --libs opencv`

#. rule used
all: $(TARGET)

$(OBJECTS) $(TARGET_O) : $(HEADERS)

$(TARGET): $(OBJECTS) $(TARGET_O)
	$(CXX) -o $@ $^ $(LIBS_CV)

#. clean command
clean:
	rm -f *o $(TARGET)
