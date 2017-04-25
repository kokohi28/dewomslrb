// Main Class DEWO
//
// 22/07/2015 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/07/2015 - 1st release, Vision for Quad copter project
//							 Fire detection module
// 22/04/2017 - Edit code style
// ...

#ifndef __DEWO_H__
#define __DEWO_H__

#include "config.h"

#if USE_BUS_I2C
	#include <linux/i2c-dev.h>
#endif // I2C Bus

#if USE_BUS_UART
	#include "Uart.h"
#endif // Uart Bus

#if USE_WIFI_LISTENER
	#include "UdpReceiver.h"
#endif // Wifi Listener

#if USE_UDP_HANDLER
	#include <pthread.h>
	#include "UdpHandler.h"
#endif // Udp Handler

#if USE_WIFI_LISTENER
	#include "UdpHandler.h"
#endif // Wifi Listener

#if USE_LIBS_OPENCV
	#include "Vision.h"
#endif // Vision-OpenCV

#if USE_SENSOR_BMP085
	#include "BMP085.h"
#endif // Sensor BMP085 (Pressure-Temperature)

#if USE_SENSOR_MPU6050
	#include "MPU6050.h"
#endif // Sensor MPU6050 (6-axis MPU)

#if USE_SENSOR_CMPS10
	#include "CMPS10.h"
#endif // Sensor CMPS10 (Compass)

class Dewo {
public:
    enum TEAM_SIDE { // see also Dewo.h base project
        SIDE_CYAN       = 65, // 'A'
        SIDE_MAGENTA    = 66, // 'B'
    };

private:

#if USE_WIFI_LISTENER
	Tools::UdpReceiver*		m_RSHLHandle;
#endif

#if USE_UDP_HANDLER
	Tools::UdpHandler*		m_BaseHandler;	
    pthread_t               mTid_BaseStation;
#endif

#if USE_BUS_UART
	Tools::Uart*			m_CommHandle;
	int						m_ActiveComm;
#endif

#if USE_LIBS_OPENCV
	Tools::Vision*			m_Vision;
#endif

#if USE_SENSOR_BMP085
	Sensors::BMP085*		m_BMPHandle;
#endif

#if USE_SENSOR_CMPS10
	Sensors::CMPS10*		m_CMPSHandle;
#endif

#if USE_SENSOR_MPU6050
	Sensors::MPU6050*		m_MPUHandle;
#endif

	static Dewo*			s_Instance; 		// Singleton reference

	unsigned int			m_MainControl;		// Main Control which used
	int						m_Command;			// Main Control which used
	int						m_PrevCommand;		// Prev Command

    int                     mRefState;
	int                     m_Side;
public:
	Dewo();
	~Dewo();

	static Dewo*			GetInstance();

	void					DestroyInstance();
	void					Init();
	void					MainLoop();

	Tools::UdpHandler*      getHandler_Base() {return m_BaseHandler;}

	int                     getTeamSide() {return m_Side;}
	void                    setTeamSide(int side) {m_Side = side;}
    int                     getState_RefState() {return mRefState;}
    void                    setState_RefState(int state) {mRefState = state;}
private:
	bool					InitConfig();
	void					DeInit();

	bool					ProcessInput();
	bool					PreProcess();
	bool					PostProcess();

	// Set - Get
	void					SetMainControl(unsigned int control);
	unsigned int			GetMainControl();
	void					SetCommand(int command);
	int						GetCommand();
	void					SetPreviousCommand(int command);
	int						GetPreviousCommand();
};

#endif /* __DEWO_H__ */