// Command List to Control Vision of Copter
//
// 22/07/2015 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/07/2015 - 1st release, Vision for Quad copter project
//							 Fire detection module
// 22/04/2017 - Edit code style
// ...

#ifndef __COMMAND_BASE_H__
#define __COMMAND_BASE_H__

#include "KeyMap.h"

namespace Command {
	enum MAIN_CONTROL {
		CONSOLE			= 0,
		UART_PRIMARY	= 1,
		UART_SECONDARY	= 2,
		NETWORK			= 3,
		SEMI_AUTO		= 4,
		FULL_AUTO		= 5,
		COUNT			= 6
	};

	enum COMMAND_CONTROL {
		XC_IDLE						= KEY_Z_SMALL
		, XC_IDLE_CAMERA_STEADY		= KEY_X_SMALL
		, XC_GRAB_TO_LOCAL			= KEY_C_SMALL
		, XC_GRAB_SEND_UART_SMALL	= KEY_V_SMALL
		, XC_KILL_APP				= KEY_Q_SMALL
	};
} //// namespace Command ////

#endif /* __COMMAND_BASE_H__ */