// Constant list
//
// Based on MSLRB github project
// 22/04/2017 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/04/2017 - 1st release, Basic Function & Constant
//							 MSLRB(Middle Size League Robo Soccer) module
// ...

#ifndef __CONSTS_H__
#define __CONSTS_H__

#include "KeyMap.h"

namespace Consts {
	enum COMMAND_REF { // See mslrb2015.pde @mslrb2015 project
		REF_START		= 115, // s
		REF_STOP		= 83, // S
		REF_DROPBALL	= 78, // N
		REF_PARK		= 76, // L
		REF_END_PART	= 104, // h
		REF_RESET		= 90, // Z
		REF_END_GAME	= 101,  // e
		REF_UNKNOWN		= 0 // <UNKNOWN>
	};

	enum CYAN_TEAM { // See mslrb2015.pde @mslrb2015 project
		CYAN_KICK_OFF		= 75, // K
		CYAN_FREE_KICK		= 70, // F
		CYAN_GOAL_KICK		= 71, // G
		CYAN_THROW_IN		= 84, // T
		CYAN_CORNER			= 67, // C
		CYAN_PENALTY		= 80, // P
		CYAN_GOAL			= 65, // A
		CYAN_REPAIR			= 79, // O
		CYAN_RED_CARD		= 82, // R
		CYAN_YELLOW_CARD	= 89, // Y
		CYAN_UNKNOWN		= 0 // <UNKNOWN>
	};

	enum MAGENTA_TEAM { // See mslrb2015.pde @mslrb2015 project
		MAG_KICK_OFF		= 107, // k
		MAG_FREE_KICK		= 102, // f
		MAG_GOAL_KICK		= 103, // g
		MAG_THROW_IN		= 116, // t
		MAG_CORNER			= 99, // c
		MAG_PENALTY			= 112, // p
		MAG_GOAL			= 97, // a
		MAG_REPAIR			= 111, // o
		MAG_RED_CARD		= 114, // r
		MAG_YELLOW_CARD		= 121,  // y
		MAG_UNKNOWN			= 0 // <UNKNOWN>
	};

	enum MAIN_CONTROL {
		CONTROL_CONSOLE		= 0,
		CONTROL_NETWORK		= 1,
		CONTROL_SEMI_AUTO	= 2,
		CONTROL_FULL_AUTO	= 3,
		CONTROL_COUNT		= 4
	};

	enum COMMAND_CONTROL {
		BASE_IDLE					= KEY_Z_SMALL
		, BASE_WAKE_UP_ROBO			= KEY_X_SMALL
		, BASE_PILOT_MODE			= KEY_C_SMALL
		, BASE_SHUTDOWN_ALL			= KEY_Q_SMALL
	};
} //// namespace Consts ////

#endif /* __CONSTS_H__ */