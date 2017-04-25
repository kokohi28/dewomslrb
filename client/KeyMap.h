// Keyboard constant Mapping
// 01/10/2014 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 01/10/2014 - 1st release, Standard Mapping(enum or define mode)
//							 RSHL(Robo Soccer Humanoid Leauge) module
// 22/04/2017 : Edit code style
// ...

#ifndef __KEYMAP_H__
#define __KEYMAP_H__

// 	Key enum
//	Used decimal value
//	Standard ASCII 0-127

#define USE_ENUM_LIST			0 // Set 0 for used define instead

// Common
#if USE_ENUM_LIST
	enum KEYMAP_COMMON {
		KEY_SPACE				= 32,
		KEY_ENTER				= 13,
		KEY_ESC					= 27,
		KEY_LINEFEED			= 10,
		KEY_BACKSPACE			= 8,
		KEY_DELETE				= 127
	};
#else
	#define KEY_SPACE			32
	#define KEY_ENTER			13
	#define KEY_ESC				27
	#define KEY_LINEFEED		10
	#define KEY_BACKSPACE		8
	#define KEY_DELETE			127
#endif

// CAPS Alphabet
#if USE_ENUM_LIST
	enum KEYMAP_CAPS_ALPHABET {
		KEY_A_CAPS				= 65,
		KEY_B_CAPS				= 66,
		KEY_C_CAPS				= 67,
		KEY_D_CAPS				= 68,
		KEY_E_CAPS				= 69,
		KEY_F_CAPS				= 70,
		KEY_G_CAPS				= 71,
		KEY_H_CAPS				= 72,
		KEY_I_CAPS				= 73,
		KEY_J_CAPS				= 74,
		KEY_K_CAPS				= 75,
		KEY_L_CAPS				= 76,
		KEY_M_CAPS				= 77,
		KEY_N_CAPS				= 78,
		KEY_O_CAPS				= 79,
		KEY_P_CAPS				= 80,
		KEY_Q_CAPS				= 81,
		KEY_R_CAPS				= 82,
		KEY_S_CAPS				= 83,
		KEY_T_CAPS				= 84,
		KEY_U_CAPS				= 85,
		KEY_V_CAPS				= 86,
		KEY_W_CAPS				= 87,
		KEY_X_CAPS				= 88,
		KEY_Y_CAPS				= 89,
		KEY_Z_CAPS				= 90
	};
#else
	#define KEY_A_CAPS			65
	#define KEY_B_CAPS			66
	#define KEY_C_CAPS			67
	#define KEY_D_CAPS			68
	#define KEY_E_CAPS			69
	#define KEY_F_CAPS			70
	#define KEY_G_CAPS			71
	#define KEY_H_CAPS			72
	#define KEY_I_CAPS			73
	#define KEY_J_CAPS			74
	#define KEY_K_CAPS			75
	#define KEY_L_CAPS			76
	#define KEY_M_CAPS			77
	#define KEY_N_CAPS			78
	#define KEY_O_CAPS			79
	#define KEY_P_CAPS			80
	#define KEY_Q_CAPS			81
	#define KEY_R_CAPS			82
	#define KEY_S_CAPS			83
	#define KEY_T_CAPS			84
	#define KEY_U_CAPS			85
	#define KEY_V_CAPS			86
	#define KEY_W_CAPS			87
	#define KEY_X_CAPS			88
	#define KEY_Y_CAPS			89
	#define KEY_Z_CAPS			90
#endif

// Small Alphabet
#if USE_ENUM_LIST
	enum KEYMAP_SMALL_ALPHABET {
		KEY_A_SMALL				= 97,
		KEY_B_SMALL				= 98,
		KEY_C_SMALL				= 99,
		KEY_D_SMALL				= 100,
		KEY_E_SMALL				= 101,
		KEY_F_SMALL				= 102,
		KEY_G_SMALL				= 103,
		KEY_H_SMALL				= 104,
		KEY_I_SMALL				= 105,
		KEY_J_SMALL				= 106,
		KEY_K_SMALL				= 107,
		KEY_L_SMALL				= 108,
		KEY_M_SMALL				= 109,
		KEY_N_SMALL				= 110,
		KEY_O_SMALL				= 111,
		KEY_P_SMALL				= 112,
		KEY_Q_SMALL				= 113,
		KEY_R_SMALL				= 114,
		KEY_S_SMALL				= 115,
		KEY_T_SMALL				= 116,
		KEY_U_SMALL				= 117,
		KEY_V_SMALL				= 118,
		KEY_W_SMALL				= 119,
		KEY_X_SMALL				= 120,
		KEY_Y_SMALL				= 121,
		KEY_Z_SMALL				= 122
	};
#else
	#define KEY_A_SMALL			97
	#define KEY_B_SMALL			98
	#define KEY_C_SMALL			99
	#define KEY_D_SMALL			100
	#define KEY_E_SMALL			101
	#define KEY_F_SMALL			102
	#define KEY_G_SMALL			103
	#define KEY_H_SMALL			104
	#define KEY_I_SMALL			105
	#define KEY_J_SMALL			106
	#define KEY_K_SMALL			107
	#define KEY_L_SMALL			108
	#define KEY_M_SMALL			109
	#define KEY_N_SMALL			110
	#define KEY_O_SMALL			111
	#define KEY_P_SMALL			112
	#define KEY_Q_SMALL			113
	#define KEY_R_SMALL			114
	#define KEY_S_SMALL			115
	#define KEY_T_SMALL			116
	#define KEY_U_SMALL			117
	#define KEY_V_SMALL			118
	#define KEY_W_SMALL			119
	#define KEY_X_SMALL			120
	#define KEY_Y_SMALL			121
	#define KEY_Z_SMALL			122
#endif

// Symbol
#if USE_ENUM_LIST
	enum KEYMAP_SYMBOL {
		KEY_DOT						= 46,
		KEY_POUND					= 35,
		KEY_QUESTION				= 63,
		KEY_EXCLAMATION				= 33,
		KEY_COMMA					= 44,
		KEY_COLON					= 58,
		KEY_SEMICOLON				= 59,
		KEY_TILDE					= 126,
		KEY_AT						= 64,
		KEY_DOLLAR					= 36,
		KEY_PERCENT					= 37,
		KEY_CARET					= 94,
		KEY_AMPERSAND				= 38,
		KEY_STAR					= 42,
		KEY_OPENPARENTHESIS			= 40,
		KEY_CLOSEPARENTHESIS		= 41,
		KEY_UNDERSCORE				= 95,
		KEY_PLUS					= 43,
		KEY_MINUS					= 45,
		KEY_EQUALS					= 61,
		KEY_BACKTICK				= 96,
		KEY_OPENBRACE				= 123,
		KEY_CLOSEBRACE				= 125,
		KEY_OPENBRACKET				= 91,
		KEY_CLOSEBRACKET			= 93,
		KEY_PIPE					= 124,
		KEY_SLASH					= 47,
		KEY_BACKSLASH				= 92,
		KEY_QUOTE					= 39,
		KEY_DOUBLEQUOTE				= 34,
		KEY_LESS					= 60,
		KEY_GREATER					= 62
	};
#else
	#define KEY_DOT					46
	#define KEY_POUND				35
	#define KEY_QUESTION			63
	#define KEY_EXCLAMATION			33
	#define KEY_COMMA				44
	#define KEY_COLON				58
	#define KEY_SEMICOLON			59
	#define KEY_HYPEN				45
	#define KEY_TILDE				126
	#define KEY_AT					64
	#define KEY_DOLLAR				36
	#define KEY_PERCENT				37
	#define KEY_CARET				94
	#define KEY_AMPERSAND			38
	#define KEY_STAR				42
	#define KEY_OPENPARENTHESIS		40
	#define KEY_CLOSEPARENTHESIS	41
	#define KEY_UNDERSCORE			95
	#define KEY_PLUS				43
	#define KEY_MINUS				KEY_HYPEN
	#define KEY_EQUALS				61
	#define KEY_BACKTICK			96
	#define KEY_OPENBRACE			123
	#define KEY_CLOSEBRACE			125
	#define KEY_OPENBRACKET			91
	#define KEY_CLOSEBRACKET		93
	#define KEY_PIPE				124
	#define KEY_SLASH				47
	#define KEY_BACKSLASH			92
	#define KEY_QUOTE				39
	#define KEY_DOUBLEQUOTE			34
	#define KEY_LESS				60
	#define KEY_GREATER				62
#endif

// Numeric
#if USE_ENUM_LIST
	enum KEYMAP_NUMERIC {
		KEY_0			= 48,
		KEY_1			= 49,
		KEY_2			= 50,
		KEY_3			= 51,
		KEY_4			= 52,
		KEY_5			= 53,
		KEY_6			= 54,
		KEY_7			= 55,
		KEY_8			= 56,
		KEY_9			= 57
	};
#else
	#define KEY_0		48
	#define KEY_1		49
	#define KEY_2		50
	#define KEY_3		51
	#define KEY_4		52
	#define KEY_5		53
	#define KEY_6		54
	#define KEY_7		55
	#define KEY_8		56
	#define KEY_9		57
#endif

#endif /* __KEYMAP_H__ */
