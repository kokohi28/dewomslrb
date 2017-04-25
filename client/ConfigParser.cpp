// Config Parser library collection
// Config Reader
// 22/07/2015 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/07/2015 - 1st release, Vision for Quad copter project
//							 Fire detection module
// 22/04/2017 - Edit code style
// ...

#include "ConfigParser.h"
#include "Tools.h"
#include <stdio.h>
#include <stdlib.h>

#define CONFIG_PATH		"cfg.cfg"

namespace Tools {
	ConfigParser::ConfigParser() {
		m_ConfigFilePath = CONFIG_PATH; // use prefine
	}

	ConfigParser::~ConfigParser() {
	}

	ConfigParser *ConfigParser::s_Instance = NULL;

	ConfigParser *ConfigParser::GetInstance() {
		if (!s_Instance) {
			DBG_N("[ConfigParser] NewInstance()");
			s_Instance = new ConfigParser;
		}
		return s_Instance;
	}

	void ConfigParser::DestroyInstance() {
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

		long l;
		unsigned int x, y, z;
		char s[20]; // 20 chars, i think enough

		// Command param's
		fscanf(pFile, "__COMMAND\n");

		fscanf(pFile, "MAIN_CONTROL: %d\n", &x);
		m_cfgMainControl = (unsigned char) x;

		// MSLRB parameter
		// Base Station
		fscanf(pFile, "__BASE_STATION\n");
		fscanf(pFile, "IP: %s\n", s);
		mBaseStation_IP = s;
		fscanf(pFile, "PORT: %d\n", &x);
		mBaseStation_Port = (unsigned int) x;
		printf("Data BaseStation:%s, %d\n", mBaseStation_IP.c_str(), mBaseStation_Port);

		// Vision param's
		fscanf(pFile, "__TRACK\n");
		fscanf(pFile, "MODE: %d\n", &x);
		m_cfgVisionMode = (unsigned char) x;
		fscanf(pFile, "WINDOW_SIZE: %d\n", &x);
		m_cfgWindowSize = (unsigned char) x;
		fscanf(pFile, "THRES_RANGE_START: %d %d %d\n", &x, &y, &z);
		m_cfgThresStartH = (unsigned char) x;
		m_cfgThresStartS = (unsigned char) y;
		m_cfgThresStartV = (unsigned char) z;
		fscanf(pFile, "THRES_RANGE_END: %d %d %d\n", &x, &y, &z);
		m_cfgThresEndH = (unsigned char) x;
		m_cfgThresEndS = (unsigned char) y;
		m_cfgThresEndV = (unsigned char) z;

		// Data Image Uart param's
		fscanf(pFile, "__UART\n");
		fscanf(pFile, "PRIMARY: %s\n", s);
		m_PrimaryUartUsed = s;
		fscanf(pFile, "PRIMARY_PORT: %ld\n", &l);
		m_PrimaryUartPort = (long) l;

		fclose(pFile); // Close file

		return true;
	}

	void ConfigParser::GetVisionParameter(unsigned char &mode, unsigned char &size,
						unsigned char &thesH1, unsigned char &thesS1, unsigned char &thesV1,
						unsigned char &thesH2, unsigned char &thesS2, unsigned char &thesV2) {
		mode = m_cfgVisionMode;
		size = m_cfgWindowSize;

		thesH1 = m_cfgThresStartH;
		thesS1 = m_cfgThresStartS;
		thesV1 = m_cfgThresStartV;

		thesH2 = m_cfgThresEndH;
		thesS2 = m_cfgThresEndS;
		thesV2 = m_cfgThresEndV;
	}

	void ConfigParser::GetCommandParameter(unsigned char &mainControl) {
		mainControl = m_cfgMainControl;
	}

} //// namespace Tools ////
