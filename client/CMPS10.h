// CMPS10 library collection - CMPS10 I2C device class
// Based on Devantech CMPS10 datasheet
// 13/09/2014 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 13/09/2014 - 1st release, Basic interfacing
//							 RSHL(Robo Soccer Humanoid Leauge) module
// 22/04/2017 - Edit code style
// ...

#ifndef __CMPS10_H__
#define __CMPS10_H__

#define USE_CMPS10_STATIC_CLASS		0 // Set 0 for Non-Static implementation

namespace Sensors {
	class CMPS10 {
	public:
		// Interfaces
	#if USE_CMPS10_STATIC_CLASS
		static void		GetBearing_Byte(uint8_t* bearing);
		static void		GetBearing_Word(uint16_t* bearing);
		static void		GetAcceleration_Byte(uint8_t* x, uint8_t* y, uint8_t* z);
		static void		GetAcceleration_Word(uint16_t* x, uint16_t* y, uint16_t* z);
		static void		GetMagnetic_Byte(uint8_t* x, uint8_t* y, uint8_t* z);
		static void		GetMagnetic_Word(uint16_t* x, uint16_t* y, uint16_t* z);
		static void		GetPitchRoll(uint8_t* pitch, uint8_t* roll);
		static bool 	CheckModule(uint8_t* version);
	#else
		void			GetBearing_Byte(uint8_t* bearing);
		void			GetBearing_Word(uint16_t* bearing);
		void			GetAcceleration_Byte(uint8_t* x, uint8_t* y, uint8_t* z);
		void			GetAcceleration_Word(uint16_t* x, uint16_t* y, uint16_t* z);
		void			GetMagnetic_Byte(uint8_t* x, uint8_t* y, uint8_t* z);
		void			GetMagnetic_Word(uint16_t* x, uint16_t* y, uint16_t* z);
		void			GetPitchRoll(uint8_t* pitch, uint8_t* roll);
		bool			CheckModule(uint8_t* version);
	#endif

		enum REGISTER_POS {
			SOFTWARE_VERSION		= 0,
			BEARING_BYTE			= 1,
			BEARING_WORD_HIGH		= 2,
			BEARING_WORD_LOW		= 3,
			PITCH_BYTE_SIGNED		= 4,
			ROLL_BYTE_SIGNED		= 5, // 6 - 9 = Empty
			MAG_X_INT_SIGNED_HIGH	= 10,
			MAG_X_INT_SIGNED_LOW	= 11,
			MAG_Y_INT_SIGNED_HIGH	= 12,
			MAG_Y_INT_SIGNED_LOW	= 13,
			MAG_Z_INT_SIGNED_HIGH	= 14,
			MAG_Z_INT_SIGNED_LOW	= 15,
			ACC_X_INT_SIGNED_HIGH	= 16,
			ACC_X_INT_SIGNED_LOW	= 17,
			ACC_Y_INT_SIGNED_HIGH	= 18,
			ACC_Y_INT_SIGNED_LOW	= 19,
			ACC_Z_INT_SIGNED_HIGH	= 20,
			ACC_Z_INT_SIGNED_LOW	= 21,
			COMMAND_REG				= 22
		};

		// Member
	#if USE_CMPS10_STATIC_CLASS
		static uint8_t		m_Buffer[12];
	#else
		uint8_t				m_Buffer[12];
	#endif
	};

} //// namespace Sensors ////

#endif /* __CMPS10_H__ */
