// CMPS10 library collection - CMPS10 I2C device class
// Based on Devantech CMPS10 datasheet
// 13/09/2014 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 13/09/2014 - 1st release, Basic interfacing
//							 RSHL(Robo Soccer Humanoid Leauge) module
// 22/04/2017 - Edit code style
// ...

#include <stdint.h> // typedef : int8_t, uint8_t, uint16_t ...
#include "CMPS10.h"
#include "I2CDev.h" // from Jeff Rowberg <jeff@rowberg.net>

#define CMPS10_ADDRESS	0x60 // default CMPS10 I2C Address,

namespace Sensors {
#if USE_CMPS10_STATIC_CLASS
	uint8_t CMPS10::m_Buffer[12]; // Static implementation
#endif

	/** Check Module
	*	By read software version at register 0x00
	*/
	bool CMPS10::CheckModule(uint8_t* version) {
		Bus::I2CDev::ReadByte(CMPS10_ADDRESS, CMPS10::SOFTWARE_VERSION, CMPS10::m_Buffer);
		*version = CMPS10::m_Buffer[0];

		if (*version > 0) // My current is 13
			return true;
		else
			return false;
	}

	/** 8-bit Bearing
	*	0 - 255 for 1 circle rotation,
	*	0/255 heading for north,
	*/
	void CMPS10::GetBearing_Byte(uint8_t* bearing) {
		Bus::I2CDev::ReadByte(CMPS10_ADDRESS, CMPS10::BEARING_BYTE, CMPS10::m_Buffer);
		*bearing = CMPS10::m_Buffer[0];
	}

	/** 16-bit Bearing
	*	0 - 3599 for 1 circle rotation,
	*	representing 0 - 359.9 degrees,
	*/
	void CMPS10::GetBearing_Word(uint16_t* bearing) {
		Bus::I2CDev::ReadBytes(CMPS10_ADDRESS, CMPS10::BEARING_WORD_HIGH, 2, CMPS10::m_Buffer);
		*bearing = (((uint16_t)CMPS10::m_Buffer[0]) << 8) | CMPS10::m_Buffer[1];
	}

	/** 8-bit X Y Z acceleration
	*	(0 - 63) = (+), (255 - 192) = (-) for 1G acceleration,
	*	(0 - 127) = (+), (255 - 128) = (-) for 2G(more) acceleration,
	*/
	void CMPS10::GetAcceleration_Byte(uint8_t* x, uint8_t* y, uint8_t* z) {
		Bus::I2CDev::ReadBytes(CMPS10_ADDRESS, CMPS10::ACC_X_INT_SIGNED_HIGH, 6, CMPS10::m_Buffer);
		*x = CMPS10::m_Buffer[0];
		*y = CMPS10::m_Buffer[2];
		*z = CMPS10::m_Buffer[4];
	}

	/** 16-bit X Y Z acceleration
	*	(0 - 16,383) = (+), (65,535 - 49,152) = (-) for 1G acceleration,
	*	(0 - 32,763) = (+), (65,535 - 32,764) = (-) for 2G(more) acceleration,
	*/
	void CMPS10::GetAcceleration_Word(uint16_t* x, uint16_t* y, uint16_t* z) {
		Bus::I2CDev::ReadBytes(CMPS10_ADDRESS, CMPS10::ACC_X_INT_SIGNED_HIGH, 6, CMPS10::m_Buffer);
		*x = (((uint16_t)CMPS10::m_Buffer[0]) << 8) | CMPS10::m_Buffer[1];
		*y = (((uint16_t)CMPS10::m_Buffer[2]) << 8) | CMPS10::m_Buffer[3];
		*z = (((uint16_t)CMPS10::m_Buffer[4]) << 8) | CMPS10::m_Buffer[5];
	}

	/** 8-bit X Y Z Magnetic
	*
	*/
	void CMPS10::GetMagnetic_Byte(uint8_t* x, uint8_t* y, uint8_t* z) {
		Bus::I2CDev::ReadBytes(CMPS10_ADDRESS, CMPS10::MAG_X_INT_SIGNED_HIGH, 6, CMPS10::m_Buffer);
		*x = CMPS10::m_Buffer[0];
		*y = CMPS10::m_Buffer[2];
		*z = CMPS10::m_Buffer[4];
	}

	/** 16-bit X Y Z Magnetic
	*
	*/
	void CMPS10::GetMagnetic_Word(uint16_t* x, uint16_t* y, uint16_t* z) {
		Bus::I2CDev::ReadBytes(CMPS10_ADDRESS, CMPS10::MAG_X_INT_SIGNED_HIGH, 6, CMPS10::m_Buffer);
		*x = (((uint16_t)CMPS10::m_Buffer[0]) << 8) | CMPS10::m_Buffer[1];
		*y = (((uint16_t)CMPS10::m_Buffer[2]) << 8) | CMPS10::m_Buffer[3];
		*z = (((uint16_t)CMPS10::m_Buffer[4]) << 8) | CMPS10::m_Buffer[5];
	}

	/** 8-bit Pitch Roll Degree
	*
	*/
	void CMPS10::GetPitchRoll(uint8_t* pitch, uint8_t* roll) {
		Bus::I2CDev::ReadBytes(CMPS10_ADDRESS, CMPS10::PITCH_BYTE_SIGNED, 2, CMPS10::m_Buffer);
		*pitch = CMPS10::m_Buffer[0];
		*roll  = CMPS10::m_Buffer[1];
	}

} //// namespace Tools ////
