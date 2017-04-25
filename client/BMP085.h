// BMP085 library collection - BMP085 I2C device class
// Based on Bosch BMP085 datasheet
// 13/09/2014 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 13/09/2014 - 1st release, Basic interfacing
//							 KOMURINDO 2014 module
// 22/04/2017 - Edit code style
// ...

#ifndef __BMP085_H__
#define __BMP085_H__

#include <stdint.h> // typedef : int8_t, uint8_t, uint16_t ...
#include "I2CDev.h" // from Jeff Rowberg <jeff@rowberg.net>

namespace Sensors {
	class BMP085 {
	private:
		// Member
		uint8_t					m_Buffer[4];

		int16_t					m_PressCoef1;
		int16_t					m_PressCoef2;
		int16_t					m_PressCoef3;
		int16_t					m_PressConst1;
		int16_t					m_PressConst2;
		int16_t					m_TempConst1;
		int16_t					m_TempConst2;
		uint16_t				m_PressConst3;
		uint16_t				m_TempCoef1;
		uint16_t				m_TempCoef2;
		long					m_TempCalc;

		// Function
		int8_t					Read(uint8_t address);
		int16_t					ReadInt(uint8_t address);
		uint16_t				ReadUT();
		long					ReadUP();

		float					GetTemperature(uint16_t ut);
		long					GetPressure(long up);
		float					GetAltitude(float pressure);

	public:
		bool					Calibrate();
		void					GetAllData(float &temperature, float &pressure, float &altitude);

		BMP085();
	};

} //// namespace Sensors ////

#endif /* __BMP085_H__ */
