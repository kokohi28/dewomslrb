// UART Serial comm library collection - uart device class
// 05/10/2014 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 05/10/2014 - 1st release, Basic interfacing
//							 RSHL(Robo Soccer Humanoid Leauge) module
// 22/04/2017 : Edit code style
// ...

#include "Uart.h"
#include "Tools.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

#define SIMPLE_DELAY			10
#define COMM_USED				1

#define BAUDRATE_COMMON			B57600
#define BAUDRATE_SECONDARY 		B9600
#define COMM_RASP				"/dev/ttyAMA0"
#define COMM_USB0				"/dev/ttyUSB0"
#define COMM_USB1				"/dev/ttyUSB1"

namespace Tools {
	Uart::Uart() {
		m_Comm = new int[COMM_USED];
	}

	Uart::~Uart() {
		SAFE_DEL_ARR(m_Comm);
	}

	bool Uart::OpenAvailableComm() {
		DBG_I("[Uart] OpenAvailableComm");
		for(register int i = 0; i < COMM_USED; i++) {
			if (!Open(m_Comm[0], COMM_USB0, BAUDRATE_COMMON))
				return false;
		}

		return true;
	}

	void Uart::CloseAvailableComm() {
		DBG_W("[Uart] CloseAvailableComm");
		for(register int i = 0; i < COMM_USED; i++) {
			Close(m_Comm[i]);
		}
	}


	int Uart::GetComm(LEVEL level) {
		return m_Comm[level];
	}

	// Open Port
	bool Uart::Open(int &uart, const char* modem, int baudrate) {
		// Open handle
		uart = open(modem, O_RDWR | O_NOCTTY | O_NDELAY);
		if (uart == -1) {
			DBG_W("[Uart] Open");
			return false;
		}

		// Get current serial port setting
		struct termios options;
		if (tcgetattr(uart, &options) == -1) {
			DBG_E("[Uart] Error Get Setting Uart");
			return false;
		}

		// Set new setting
		options.c_cflag |= baudrate;
		options.c_cflag |= CS8;
		options.c_cflag |= CLOCAL;
		options.c_cflag |= CREAD;
		options.c_iflag = IGNPAR;
		options.c_oflag = 0;
		options.c_lflag = 0;

		tcflush(uart, TCIFLUSH);
		tcsetattr(uart, TCSANOW, &options);

		return true;
	}

	// Close Port
	void Uart::Close(int &uart) {
		close(uart);
	}

	// Test Uart
	void Uart::Test() {
		DBG_I("[Uart] Test Send Data");
		for(register int i = 0; i < COMM_USED; i++)
		{
			Test(m_Comm[i]);
		}
	}

	void Uart::Test(int uart) {
		// Capital letter test
		for(register unsigned char i = 0; i < 26; i++) {
			int data = i + KEY_A_CAPS;
			Send(data, uart);
			Tools::SimpleWait(SIMPLE_DELAY);
		}
		Send(KEY_ENTER, uart);
		Send(KEY_ENTER, uart);

		// Lower letter test
		for(register unsigned char i = 0; i < 26; i++) {
			int data = i + KEY_A_SMALL;
			Send(data, uart);
			Tools::SimpleWait(SIMPLE_DELAY);
		}
		Send(KEY_ENTER, uart);
		Send(KEY_ENTER, uart);

		// Number test
		for(register unsigned char i = 0; i < 10; i++) {
			int data = i + KEY_0;
			Send(data, uart);
			Tools::SimpleWait(SIMPLE_DELAY);
		}
		Send(KEY_ENTER, uart);
		Send(KEY_ENTER, uart);
	}

	// Send Data
	void Uart::Send(int data) {
		for(register int i = 0; i < COMM_USED; i++) {
			Send(data, m_Comm[i]);
		}
	}

	void Uart::Send(int data, int uart) {
		int nData, tmpData;
		char buffData[1];
		tmpData = data;
		buffData[0] = tmpData;
		if (uart != -1) {
			nData = write(uart, buffData, 1);
			if (nData < 0) {
				DBG_E("[Uart] Send Error!");
			}
		} else {
			DBG_E("[Uart] TX Error!");
		}
	}

	// Send in Digit Format
	void Uart::SendDigit(long data, int length, int uart, int delay) {
		// Get
		int data_i[6];
		for (register int i = 0; i < length ; i++) {
			data_i[i] = data % 10;
			data = data / 10;
		}

		// Send
		for (register int i = (length - 1); i >= 0; i--) {
			Send(data_i[i] + 0x30, uart); // as ASCII
			Tools::SimpleWait(delay);
		}
	}

	// Read Data
	int Uart::Read(int uart) {
		if (uart != -1) {
			// Read per byte
			unsigned char buffData[1];
			int length = read(uart, (void*)buffData, 1);

			if (length < 0 || length == 0) {
				return -1; // No Data
			} else {
				return buffData[0]; // Process Data
			}
		} else {
			DBG_E("[Uart] RX Error!");
		}
		return -1;
	}

} //// namespace Tools ////
