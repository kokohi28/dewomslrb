// Config Parser library collection
// Config Reader
// 22/07/2015 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/07/2015 - 1st release, Vision for Quad copter project
//							 Fire detection module
// 22/04/2017 - 2nd release, Porting vars and function for MSLRB
// ...

#include "ConfigParser.h"
#include "Tools.h"
#include <stdio.h>
#include <stdlib.h>

#define CONFIG_PATH		"cfg.cfg"

namespace Tools {
	ConfigParser::ConfigParser() {
		m_ConfigFilePath = CONFIG_PATH; // use pre-define
	}

	ConfigParser::~ConfigParser() {
	}

	ConfigParser *ConfigParser::s_Instance = NULL;

	ConfigParser *ConfigParser::GetInst() {
		if (!s_Instance) {
			DBG_N("[ConfigParser] NewInstance()");
			s_Instance = new ConfigParser;
		}
		return s_Instance;
	}

	void ConfigParser::DestroyInst() {
		SAFE_DEL(s_Instance);
		DBG_W("[ConfigParser] DestroyInstance()");
	}

	void ConfigParser::SetFilePath(std::string path) {
		m_ConfigFilePath = path;
	}

	bool ConfigParser::Init(std::string path) {
		m_ConfigFilePath = path;
		return Init();
	}

	bool ConfigParser::Init() {
		printf("[ConfigParser] Init:%s\n", m_ConfigFilePath.c_str());

		// Get Config File path
		FILE *pFile = fopen(m_ConfigFilePath.c_str(), "r");

		if (!pFile) {
			DBG_W("[ConfigParser] Fail Open File, use default instead");
			pFile = fopen(CONFIG_PATH, "r");
		}

		unsigned int x;
		char s[20]; // 20 chars, i think enough

		// Command param's
		fscanf(pFile, "__COMMAND\n");

		fscanf(pFile, "MAIN_CONTROL: %d\n", &x);
		m_cfgMainControl = (unsigned char) x;

		// MSLRB parameter
		// Referee Box
		fscanf(pFile, "__REF_BOX\n");
		fscanf(pFile, "IP: %s\n", s);
		mRefBox_IP = s;
		fscanf(pFile, "PORT: %d\n", &x);
		mRefBox_Port = (unsigned int) x;
		printf("Data RefBox:%s, %d\n", mRefBox_IP.c_str(), mRefBox_Port);

		// Base Station
		fscanf(pFile, "__BASE_STATION\n");
		fscanf(pFile, "UDP_PORT: %d\n", &x);
		mBase_Udp_Port = (unsigned int) x;
		printf("Data Udp Base:%d\n", mBase_Udp_Port);

		// Robo 1
		fscanf(pFile, "__ROBO_1\n");
		fscanf(pFile, "IP: %s\n", s);
		mRobo_1_IP = s;
		printf("Data Robo 1:%s\n", mRobo_1_IP.c_str());

		// Robo 2
		fscanf(pFile, "__ROBO_2\n");
		fscanf(pFile, "IP: %s\n", s);
		mRobo_2_IP = s;
		printf("Data Robo 2:%s\n", mRobo_2_IP.c_str());

		// Robo 3
		fscanf(pFile, "__ROBO_3\n");
		fscanf(pFile, "IP: %s\n", s);
		mRobo_3_IP = s;
		printf("Data Robo 3:%s\n", mRobo_3_IP.c_str());

		return true;
	}

	void ConfigParser::GetCommandParameter(unsigned char &mainControl) {
		mainControl = m_cfgMainControl;
	}

} //// namespace Tools ////
