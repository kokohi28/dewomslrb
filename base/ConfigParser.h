// Config Parser library collection
// Config Reader
// 22/07/2015 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/07/2015 - 1st release, Vision for Quad copter project
//							 Fire detection module
// 22/04/2017 - 2nd release, Porting vars and function for MSLRB
// ...

#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include <iostream>

namespace Tools {
	class ConfigParser {
	private:
		std::string				m_ConfigFilePath;

		static ConfigParser*	s_Instance;

		/******************************************/
		// MSLRB parameter
		std::string 			mRefBox_IP;
		unsigned int 			mRefBox_Port;
		unsigned int 			mBase_Udp_Port;
		std::string 			mRobo_1_IP;
		std::string 			mRobo_2_IP;
		std::string 			mRobo_3_IP;

		// Command param's
		unsigned char 			m_cfgMainControl;
		/******************************************/

	public:
		ConfigParser();
		~ConfigParser();

		static ConfigParser*	GetInst();

		void					DestroyInst();
		void 					SetFilePath(std::string path);
		bool					Init();
		bool					Init(std::string path);

		/******************************************/
		// Command param's
		void					GetCommandParameter(unsigned char &mainControl);

		std::string				GetRefBox_IP() {return mRefBox_IP;} // inline saja 
		unsigned int			GetRefBox_Port() {return mRefBox_Port;} // inline saja
		unsigned int			GetBase_Udp_Port() {return mBase_Udp_Port;} // inline saja
		std::string				GetRobo_1_IP() {return mRobo_1_IP;} // inline saja
		std::string				GetRobo_2_IP() {return mRobo_2_IP;} // inline saja
		std::string				GetRobo_3_IP() {return mRobo_3_IP;} // inline saja
	};

} //// namespace Tools ////

#endif /* __CONFIG_PARSER_H__ */
