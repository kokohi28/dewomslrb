// TCP HANDLER library collection - TcpHandler device class
// Based on MSLRB github project
// 22/04/2017 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/04/2017 - 1st release, Basic Function & Constant
//							 MSLRB(Middle Size League Robo Soccer) module
// ...

#include "TcpHandler.h"
#include "Tools.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h> 
#include <string.h>

#define DEFAULT_PORT		"28097" // refer to MSLRB WiFi rulebook
#define DEFAULT_SERVER		"192.168.1.2"

namespace Tools {
	TcpHandler::TcpHandler() : mbIsReady(false) {
		mServerIP = DEFAULT_SERVER;
		mPort = atoi(DEFAULT_PORT);	    	    
	}

	TcpHandler::TcpHandler(const char *server, unsigned int port) : mbIsReady(false) {
		mServerIP = server;
		mPort = port;
	}

	TcpHandler::~TcpHandler() {
		EndSocket();
	}

	bool TcpHandler::Init() {
		int n;
	    struct sockaddr_in	serv_addr;
	    struct hostent		*server;

	    mSockfd = socket(AF_INET, SOCK_STREAM, 0);
	    if (mSockfd < 0) {
	        DBG_E("[TcpHandler] ERROR opening socket");
	        return false;
	    }

	    server = gethostbyname(mServerIP);
	    if (server == NULL) {
	        DBG_E("[TcpHandler] ERROR, no such host");
	        EndSocket();
	        return false;
	    }

	    bzero((char *) &serv_addr, sizeof(serv_addr));
	    serv_addr.sin_family = AF_INET;
	    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	    serv_addr.sin_port = htons(mPort);

	    if (connect(mSockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
	        DBG_E("[TcpHandler] ERROR connecting");
	        EndSocket();
	        return false;
	    }

		mbIsReady = true; // mark as ready
	    return true;
	}

	void TcpHandler::EndSocket() {
		DBG_N("[TcpHandler] Socket deleted");
		close(mSockfd);
	}

	int TcpHandler::ReadData() {
		if (!mbIsReady) return -1;

		bzero(mBuffer, DATA_BUFFER_SIZE);
    	int n = read(mSockfd, mBuffer, DATA_BUFFER_SIZE);
    	if (n < 0) { 
        	DBG_E("[TcpHandler] ERROR reading from socket");
     	}
    	// printf("[TcpHandler] length:%d, data:%s\n", strlen(mBuffer), mBuffer);

     	/************* TODO!!! Fix the logic *************/

     	// Just get last item
     	int ndata = strlen(mBuffer);
     	if (ndata > 0) {
    		return mBuffer[ndata - 1];
    	} else {
    		return -1;
    	}
	}

	void TcpHandler::WriteData(std::string data) {
		if (!mbIsReady) return;

		bzero(mBuffer, DATA_BUFFER_SIZE);
    	// mBuffer = data.c_str();

    	int n = write(mSockfd, mBuffer, strlen(mBuffer));
    	if (n < 0) {
        	DBG_E("[TcpHandler] ERROR writing to socket");
     	}
	}

	void TcpHandler::WriteData(int ascii_data) {
		if (!mbIsReady) return;

	}
} //// namespace Tools ////
