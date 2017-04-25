// Config Parser library collection
// Config Reader
// 22/07/2015 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/07/2015 - 1st release, Vision for Quad copter project
//							 Fire detection module
// 22/04/2017 - Edit code style
// 24/04/2017 - MSLRB
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
		// QuadCopter parameter
		// Vision param's
		unsigned char 			m_cfgVisionMode;
		unsigned char 			m_cfgWindowSize;

		unsigned char 			m_cfgThresStartH;
		unsigned char 			m_cfgThresStartS;
		unsigned char 			m_cfgThresStartV;

		unsigned char 			m_cfgThresEndH;
		unsigned char 			m_cfgThresEndS;
		unsigned char 			m_cfgThresEndV;

		// Command param's
		unsigned char 			m_cfgMainControl;

		// Data Image Uart param's
		unsigned char 			m_cfgSendImageUartMode;
		int 					m_cfgSendImageUartDelayMain;
		int 					m_cfgSendImageUartDelaySend;
		/******************************************/
		// MSLRB parameter
		std::string 			mBaseStation_IP;
		unsigned int 			mBaseStation_Port;
	public:
		ConfigParser();
		~ConfigParser();

		static ConfigParser*	GetInstance();

		void					DestroyInstance();
		void 					SetFilePath(std::string path);
		bool					Init();
		bool					Init(std::string path);

		/******************************************/
		// QuadCopter parameter
		// Vision param's
		void					GetVisionParameter(
									unsigned char &mode, unsigned char &size,
									unsigned char &thesH1, unsigned char &thesS1, unsigned char &thesV1,
									unsigned char &thesH2, unsigned char &thesS2, unsigned char &thesV2
									);
		// Command param's
		void					GetCommandParameter(unsigned char &mainControl);

		// Data Image Uart param's
		void					GetSendImageUartParameter(unsigned char &mode, int &delayMain, int &delaySend);
		/******************************************/

		std::string				GetBaseStation_IP() {return mBaseStation_IP;} // inline saja 
		unsigned int			GetBaseStation_Port() {return mBaseStation_Port;} // inline saja
	};

} //// namespace Tools ////

#endif /* __CONFIG_PARSER_H__ */
