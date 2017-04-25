// Main Class DEWO
//
// 22/07/2015 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/07/2015 - 1st release, Vision for Quad copter project
//							 Fire detection module
// 22/04/2017 - Edit code style
// ...

/****************************************************/
/****************************************************/
/******************* Header *************************/
#include "Dewo.h"
#include "ConfigParser.h"
#include "CommandBase.h"
#include <stdint.h> // typedef : int8_t, uint8_t, uint16_t ...
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define THREAD_ID_BASE_STATION	100 // Unique
#define THREAD_ID_ROBO        	101 // Unique

/******************* ADDITIONAL VAR's ***************/
std::string gConfigPath = "";
unsigned int gCountPic = 0;

bool                    g_BASE_STATION_LOOP = true;      // Control the life of TCP RefBoxHandler
bool                    g_MAIN_LOOP = true;         // Control the life of the program

/******************* Prototype **********************/
void *_thread_udp_base_station(void *vargp);

/****************************************************/
/****************************************************/
/******************* MAIN ***************************/
int main(int argc, const char *argv[]) {
	DBG_N("[MAIN] >> START!");

	if (argc > 1) {
        gConfigPath = argv[1]; // use only second param's
    } else {
		DBG_W("[MAIN] Not passing config file, use predefined instead!");
    }

	// Init module
	Dewo::GetInstance()->Init();

	// Loop
	Dewo::GetInstance()->MainLoop();

	// End
	Dewo::GetInstance()->DestroyInstance(); // release all memory
	DBG_N("[MAIN] END!!! <<");

	return 0;
}

/****************************************************/
/****************************************************/
/******************* DEWO ***************************/
Dewo *Dewo::s_Instance = NULL;

Dewo *Dewo::GetInstance() {
	if (!s_Instance) {
		DBG_W("[Dewo] NewInstance()");
		s_Instance = new Dewo;
	}
	return s_Instance;
}

void Dewo::DestroyInstance() {
	// DeInit first
	DeInit();

	// Release all
#if USE_WIFI_LISTENER
	SAFE_DEL(m_RSHLHandle);
#endif

#if USE_UDP_HANDLER
	SAFE_DEL(m_BaseHandler);
#endif

#if USE_BUS_UART
	SAFE_DEL(m_CommHandle);
#endif

#if USE_LIBS_OPENCV
	SAFE_DEL(m_Vision);
#endif

#if USE_SENSOR_BMP085
	SAFE_DEL(m_BMPHandle);
#endif

#if USE_SENSOR_CMPS10
	SAFE_DEL(m_CMPSHandle);
#endif

#if USE_SENSOR_MPU6050
	SAFE_DEL(m_MPUHandle);
#endif

	SAFE_DEL(s_Instance);
	DBG_W("[Dewo] DestroyInstance()");
}

// Primary Init's
void Dewo::Init() {
	InitConfig(); // Read config first

	// Instance all here
#if USE_WIFI_LISTENER
	m_RSHLHandle 	= new Tools::UdpReceiver();
#endif

#if USE_UDP_HANDLER
    unsigned int base_port 	= Tools::ConfigParser::GetInstance()->GetBaseStation_Port(); 
    std::string base_server = Tools::ConfigParser::GetInstance()->GetBaseStation_IP();
    m_BaseHandler           = new Tools::UdpHandler(base_server.c_str(), base_port);
    if (!m_BaseHandler->Init()) {
        DBG_E("[Dewo] Udp Base Station Not ready");
    } else {
        // m_BaseHandler->WriteData(std::string("START"));
    }

	// Create Thread and Loop for Base Station
    pthread_create(&mTid_BaseStation, NULL, _thread_udp_base_station, (void *) THREAD_ID_BASE_STATION);
#endif

#if USE_BUS_UART
	m_CommHandle 	= new Tools::Uart();
	if (!m_CommHandle->OpenAvailableComm()) {
		DBG_E("[Dewo] Uart not ready");
	} else {
		m_CommHandle->Test();

		// init first uart port
		m_ActiveComm = m_CommHandle->GetComm(MAIN); // Use this for primary uart comm
	}
#endif

#if USE_LIBS_OPENCV
	m_Vision 		= new Tools::Vision();
	if (!m_Vision->Init()) {
		DBG_E("[Dewo] Vision module not ready");
	} else {

	}
#endif

#if USE_SENSOR_CMPS10
	m_CMPSHandle	= new Sensors::CMPS10();
	uint8_t version;
	if (!m_CMPSHandle->CheckModule(&version)) {
		DBG_E("[Dewo] CMPS10 not ready");
	} else {
		// Test print sensor value
		uint8_t acc_X, acc_Y, acc_Z;
		m_CMPSHandle->GetAcceleration_Byte(&acc_X, &acc_Y, &acc_Z);
		printf("[Dewo] CMPS10 Data Test: %d, %d, %d\n", acc_X, acc_Y, acc_Z);
	}
#endif

#if USE_SENSOR_BMP085
	m_BMPHandle 	= new Sensors::BMP085();
	if (!m_BMPHandle->Calibrate()) {
		DBG_E("[Dewo] BMP085 not ready");
	} else {
		// Test print sensor value
		float temperature, pressure, altitude;
		m_BMPHandle->GetAllData(temperature, pressure, altitude);
		printf("[Dewo] BMP085 Data Test: %.2f, %.2f, %.2f\n", temperature, pressure, altitude);
	}
#endif

#if USE_SENSOR_MPU6050
	m_MPUHandle 	= new Sensors::MPU6050();
	// Init sensor module
	m_MPUHandle->initialize();
	bool mpu6050Ready = m_MPUHandle->testConnection();
	if (!mpu6050Ready) {
		DBG_E("[Dewo] MPU6050 Not Detected!");
	} else {
		// Test print sensor value
		int16_t ax, ay, az, gx, gy, gz;
		m_MPUHandle->getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
		printf("[Dewo] MPU6050 Data Test: %d, %d, %d, %d, %d, %d\n", ax, ay, az, gx, gy, gz);
	}
#endif
}

bool Dewo::InitConfig() {
	// Read config file
	if (gConfigPath.empty()) {
		Tools::ConfigParser::GetInstance()->Init();
	} else {
		Tools::ConfigParser::GetInstance()->Init(gConfigPath);
	}

	unsigned char temp1, temp2;
	Tools::ConfigParser::GetInstance()->GetCommandParameter(temp1);
	SetMainControl((unsigned int) temp1);

	return true;
}

// Primary DeInit
void Dewo::DeInit() {
#if USE_BUS_UART
	m_CommHandle->CloseAvailableComm();
#endif
}

bool Dewo::ProcessInput() {
	switch (GetMainControl()) {
		/*** Console(Terminal) Input by keyboard stroke ***/
		case Command::CONSOLE: {
			if (Tools::KeyHit()) {
				int command = (int) getchar();
				printf("[DEWO] Keyboard Input: %d\n", command);
				SetCommand(command);
			}
		}
			break;
		/*** Uart primary data ***/
		case Command::UART_PRIMARY: {
			int uartData = 0;
			uartData = m_CommHandle->Read(m_ActiveComm);
			if (uartData != -1) {
				printf("[DEWO] Comm Input: %d\n", uartData);
				SetCommand(uartData);
			}
		}
			break;
		/*** Uart secondary data ***/
		case Command::UART_SECONDARY:
			break;
		/*** Tcp/Udp(Network) data ***/
		case Command::NETWORK:
			break;
		// TODO
		case Command::SEMI_AUTO:
			break;
		// TODO
		case Command::FULL_AUTO:
			break;
		default:
			DBG_W("[Dewo] INPUT MODE NOT DEFINED!");
			break;
	}

	return true;
}

bool Dewo::PreProcess() {
	switch (GetCommand()) {
		case Command::XC_IDLE: {
			//DBG_I("[Dewo] Command::XC_IDLE");
		}
			break;
		case Command::XC_IDLE_CAMERA_STEADY: {
			// DBG_I("[Dewo] Command::XC_IDLE_CAMERA_STEADY");
			if (!m_Vision->Update()) return false;

			// Get param to send
			uint16_t posx, posy;

			m_Vision->GetObjectLocation(posx, posy);
			printf("... To Robo:%d %d %d\n", posx, posy, mRefState);

			// Send
			int uart = m_CommHandle->GetComm(MAIN);
			m_CommHandle->SendDigit((long) posx, 3, uart, 1);
			m_CommHandle->Send(65); // 'A'
			m_CommHandle->SendDigit((long) posy, 3, uart, 1);
			m_CommHandle->Send(68); // 'D'
			m_CommHandle->Send(mRefState); // wifi
			m_CommHandle->Send(13); // enter				
		}
			break;
		case Command::XC_GRAB_TO_LOCAL: {
			DBG_I("[Dewo] Command::XC_GRAB_TO_LOCAL");
			if (!m_Vision->Update()) return false;

			std::string fileName = "Captured_" + Tools::Time::GetDenseFormatTime() + ".jpg";
			m_Vision->SaveCapturedFrame(fileName);
			SetCommand((int) Command::XC_IDLE_CAMERA_STEADY);
		}
			break;
		case Command::XC_GRAB_SEND_UART_SMALL: {
			DBG_I("[Dewo] Command::XC_GRAB_SEND_UART_SMALL");
			// unsigned char temp1;
			// int temp2, temp3;
			// Tools::ConfigParser::GetInstance()->GetSendImageUartParameter(temp1, temp2, temp3); // temp3 as delaySend
			// m_Vision->SendViaUart(temp3, m_CommHandle);
			SetCommand((int) Command::XC_IDLE_CAMERA_STEADY);
		}
			break;
		case Command::XC_KILL_APP: {
			return false;
		}
			break;
		default:
			break;
	}
	return true;
}

bool Dewo::PostProcess() {
	return true;
}

// Main Loop
void Dewo::MainLoop() {
	while (g_MAIN_LOOP) {
		/*** INPUT ***/
		if (!ProcessInput()) break;

		/*** PRE PROCESS ***/
		if (!PreProcess()) break;

		/*** POST PROCESS ***/
		if (!PostProcess()) break;
	}
}

void *_thread_udp_base_station(void *vargp) {
    // int tid = (int) vargp;

    while (g_BASE_STATION_LOOP) {
    	// Request first!!!
    	Dewo::GetInstance()->getHandler_Base()->SendTo("SEND_ME_COMMAND");

    	// Read Data!!!
        std::string data = Dewo::GetInstance()->getHandler_Base()->ReadData();
        // TODO!!! Recheck data from client and process based command/instruction/request format

        // printf("Ref Udp Base Data:%s\n", data.c_str());

        // Save state;
        Dewo::GetInstance()->setState_RefState(data[0]);
    }

    DBG_I("[Dewo] _thread_tcp_refbox STOP!!!");
}

Dewo::Dewo():
  m_MainControl((unsigned int) Command::CONSOLE)
, m_ActiveComm(0)
, m_Command(Command::XC_IDLE_CAMERA_STEADY)
, m_PrevCommand(Command::XC_IDLE_CAMERA_STEADY) {
//////////////////////////////////////////////////////// CHECK Active FLAG
////////////////////////// Bus
#if USE_BUS_I2C
	DBG_N("[Dewo] BUS I2C Active (v)");
#endif // I2C

#if USE_BUS_UART
	DBG_N("[Dewo] BUS UART Active (v)");
#endif // UART

////////////////////////// Sensor
#if USE_SENSOR_MPU6050
	DBG_N("[Dewo] SENSOR MPU6050 Active (v)");
#endif // MPU6050

#if USE_SENSOR_HMC5883L
	DBG_N("[Dewo] SENSOR HMC5883L Active (v)");
#endif // HMC5883L

#if USE_SENSOR_BMP085
	DBG_N("[Dewo] SENSOR BMP085 Active (v)");
#endif // BMP085

#if USE_SENSOR_CMPS10
	DBG_N("[Dewo] SENSOR CMPS10 Active (v)");
#endif // CMPS10

////////////////////////// Libs
#if USE_LIBS_OPENCV
	DBG_N("[Dewo] LIBS OPENCV Active (v)");
#endif // Vision-OpenCV

#if USE_WIFI_LISTENER
	DBG_N("[Dewo] LIBS RSHL WIFI LISTENER Active (v)");
#endif // Wifi (UDP) Listener

}

Dewo::~Dewo() {
	DBG_W("[Dewo] Destruct()");
}

/****************************************************/
/******************* Set - Get **********************/
// Main Control
void Dewo::SetMainControl(unsigned int control) {
	printf("[Dewo] SetMainControl():%d\n", control);
	m_MainControl = control;
}

unsigned int Dewo::GetMainControl() {
	return m_MainControl;
}

// Active Command
void Dewo::SetCommand(int command) {
	m_Command = command;
}

int Dewo::GetCommand() {
	return m_Command;
}

void Dewo::SetPreviousCommand(int command) {
	m_PrevCommand = command;
}

int Dewo::GetPreviousCommand() {
	return m_PrevCommand;
}

/******************* END of DEWO ********************/
/****************************************************/
/****************************************************/
