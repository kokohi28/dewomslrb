// Standard Tools - Namespace Tools
// 13/09/2014 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 13/09/2014 - 1st release, Basic Function & Constant
//							 RSHL(Robo Soccer Humanoid Leauge) module
// 22/04/2017 : Edit code style
// ...

#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdio.h>
#include <iostream>
#include "KeyMap.h" // Key constant mapping

namespace Tools {
	// Wait multiply 1000
	void SimpleWait(long _x1000);

	// Getche() like in Conio.h WIN32
	int Getche();

	// Getch() like in Conio.h WIN32
	char Getch();

	// Keyboard Hit
	bool KeyHit();

	// Time utility
	class Time {
	public:
		static int GetYear();
		static int GetMonth();
		static int GetDate();
		static int GetHour();
		static int GetMinute();
		static int GetSecond();
		static std::string GetDenseFormatTime();
	};

} //// namespace Tools ////

// GENERAL CONSTANT
// Terminal Font Color, see http://en.wikipedia.org/wiki/ANSI_escape_code#Colors
#define ANSI_COLOR_RED		"\x1b[31m"
#define ANSI_COLOR_GREEN	"\x1b[32m"
#define ANSI_COLOR_YELLOW	"\x1b[33m"
#define ANSI_COLOR_BLUE		"\x1b[34m"
#define ANSI_COLOR_MAGENTA	"\x1b[35m"
#define ANSI_COLOR_CYAN		"\x1b[36m"
#define ANSI_COLOR_RESET	"\x1b[0m"

// General Debug Print
enum DBG_TYPE {
	DBG_INFO		= 0,
	DBG_WARNING		= 1,
	DBG_ERROR		= 2
};

// General access level
enum LEVEL {
	MAIN			= 0,
	SECOND			= 1,
	THIRD			= 2
};

#define DBG(...)			printf(						"%s\n"				   , __VA_ARGS__);
#define DBG_N(...)			printf(						"%s\n"				   , __VA_ARGS__);
#define DBG_I(...)			printf(ANSI_COLOR_GREEN		"%s\n" ANSI_COLOR_RESET, __VA_ARGS__); // print use green font color
#define DBG_W(...)			printf(ANSI_COLOR_YELLOW	"%s\n" ANSI_COLOR_RESET, __VA_ARGS__); // print use yellow font color
#define DBG_E(...)			printf(ANSI_COLOR_RED		"%s\n" ANSI_COLOR_RESET, __VA_ARGS__); // print use red font color
#define DBG_OFF(...)		{} // disable print debug

// Safe Delete 1 Pointer
#define SAFE_DEL(ptr) \
	if(ptr) { \
		delete ptr; \
		ptr = NULL; \
	}

// Safe Delete Array Pointer
#define SAFE_DEL_ARR(ptr) \
	if (ptr) { \
		delete[] ptr; \
		ptr = NULL; \
	}

// Singleton Instance
#define INSTANCE(cName, iName) \
	if(!iName) { \
		iName = new cName; \
	} \
	return iName;

#endif /* __TOOLS_H__ */
