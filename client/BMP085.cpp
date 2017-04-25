// BMP085 library collection - BMP085 I2C device class
// Based on Bosch BMP085 datasheet
// 13/09/2014 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 13/09/2014 - 1st release, Basic interfacing
//							 KOMURINDO 2014 module
// 22/04/2017 - Edit code style
// ...

#include <math.h>
#include "BMP085.h"

// COMMON ADDRESS
#define BMP085_ADDRESS		0x77
#define OSS					0 // oversampling

namespace Sensors {
	BMP085::BMP085() {
	}

	bool BMP085::Calibrate() {
		m_PressCoef1	= ReadInt(0xAA);
		m_PressCoef2	= ReadInt(0xAC);
		m_PressCoef3	= ReadInt(0xAE);
		m_PressConst3	= ReadInt(0xB0);
		m_TempCoef1		= ReadInt(0xB2);
		m_TempCoef2		= ReadInt(0xB4);
		m_PressConst1	= ReadInt(0xB6);
		m_PressConst2	= ReadInt(0xB8);
						  ReadInt(0xBA); // seems nothing do
		m_TempConst1	= ReadInt(0xBC);
		m_TempConst2	= ReadInt(0xBE);

		// Check if, module is ready W.I.P
		if (m_PressCoef1 == 8155) // this constant found from trial
			return true;
		else
			return false;
	}

	int16_t BMP085::ReadInt(uint8_t address) {
		Bus::I2CDev::ReadBytes(BMP085_ADDRESS, address, 2, m_Buffer);
		return (((int16_t)m_Buffer[0]) << 8) | (int16_t)m_Buffer[1];
	}

	int8_t BMP085::Read(uint8_t address) {
		Bus::I2CDev::ReadByte(BMP085_ADDRESS, address, m_Buffer);
		return (int8_t)m_Buffer[0];
	}

	long BMP085::ReadUP() {
		// Write 0x34 + (OSS << 6) to 0xF4
		Bus::I2CDev::WriteByte256(BMP085_ADDRESS, 0xF4, 0x34 + (OSS << 6)); // use special write, NEED to Fix!
		// Process
		Bus::I2CDev::ReadBytes(BMP085_ADDRESS, 0xF6, 3, m_Buffer); // read 3 bytes from 0xF6
		return (((long)m_Buffer[0] << 16) | ((long)m_Buffer[1] << 8) | (long)m_Buffer[2]) >> (8 - OSS);
	}

	uint16_t BMP085::ReadUT() {
		// Write 0x34 + (OSS << 6) to 0xF4
		Bus::I2CDev::WriteByte256(BMP085_ADDRESS, 0xF4, 0x2E); // use special write, NEED to Fix!
		// Process
		return ReadInt(0xF6);
	}

	long BMP085::GetPressure(long up) {
		long x1, x2, x3, b3, b6, p;
		unsigned long b4, b7;

		//
		b6 = m_TempCalc - 4000;

		// Calculate B3
		x1 = (m_PressConst2 * (b6 * b6) >> 12) >> 11;
		x2 = (m_PressCoef2 * b6) >> 11;
		x3 = x1 + x2;
		b3 = (((((long)m_PressCoef1) * 4 + x3) << OSS) + 2) >> 2;

		// Calculate B4
		x1 = (m_PressCoef3 * b6) >> 13;
		x2 = (m_PressConst1 * ((b6 * b6) >> 12)) >> 16;
		x3 = ((x1 + x2) + 2) >> 2;
		b4 = (m_PressConst3 * (unsigned long)(x3 + 32768)) >> 15;

		//
		b7 = ((unsigned long)(up - b3) * (50000 >> OSS));
		if (b7 < 0x80000000)	p = (b7 << 1) / b4;
		else					p = (b7 / b4) << 1;

		//
		x1 = (p >> 8) * (p >> 8);
		x1 = (x1 * 3038) >> 16;
		x2 = (-7357 * p) >> 16;
		p += (x1 + x2 + 3791) >> 4;

		//
		return p;
	}

	float BMP085::GetTemperature(uint16_t ut) {
		long x1, x2;
		float temp;

		x1 = (((long)ut - (long)m_TempCoef2) * (long)m_TempCoef1) >> 15;
		x2 = ((long)m_TempConst1 << 11) / (x1 + m_TempConst2);

		m_TempCalc = x1 + x2;
		temp = ((m_TempCalc + 8) >> 4);
		return (temp / 10);
	}

	float BMP085::GetAltitude(float pressure) {
		float A = pressure / 101325;
		float B = 1 / 5.25588;
		float C = pow(A, B);
		C = 1 - C;
		C = C / 0.0000225577;
		return C;
	}

	void BMP085::GetAllData(float &temperature, float &pressure, float &altitude) {
		temperature	= GetTemperature(ReadUT());
		pressure	= GetPressure(ReadUP());
		altitude	= GetAltitude(pressure);
	}

} //// namespace Sensors ////