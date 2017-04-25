// UDP HANDLER library collection - UdpHandler device class
// Based on MSLRB github project
// 22/04/2017 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/04/2017 - 1st release, Basic Function & Constant
//							 MSLRB(Middle Size League Robo Soccer) module
// ...

#include "UdpHandler.h"
#include "Tools.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <arpa/inet.h>

#define DEFAULT_PORT		"30001" // see cfg.cfg
#define DEFAULT_SERVER		"192.168.0.101"

namespace Tools {
	UdpHandler::UdpHandler() :
		mServerIP(DEFAULT_SERVER),
		mPort(atoi(DEFAULT_PORT)),
		mMode(UDP_CLIENT),
		mbIsReady(false) {
	}

	UdpHandler::UdpHandler(unsigned int port) : mbIsReady(false) {
		mPort = port;
		mMode = UDP_SERVER;
	}

	UdpHandler::UdpHandler(const char *server, unsigned int port) : mbIsReady(false) {
		mServerIP = server;
		mPort = port;
		mMode = UDP_CLIENT;
	}

	UdpHandler::~UdpHandler() {
		EndSocket();
	}

	bool UdpHandler::Init() {
		int n;

		mClientaddrlen = sizeof(mClientaddr);
		mServeraddrlen = sizeof(mServeraddr);

		mSockfd = socket(AF_INET, SOCK_DGRAM, 0);
		if (mSockfd < 0) {
			DBG_E("[UdpHandler] ERROR opening socket");
			return false;
		}

		/* bind to address */
		memset(&mServeraddr, 0x00, mServeraddrlen);
		mServeraddr.sin_family = AF_INET;
		mServeraddr.sin_port = htons(mPort);
		mServeraddr.sin_addr.s_addr = htonl(INADDR_ANY);
		if ((n = bind(mSockfd, (struct sockaddr *) &mServeraddr, mServeraddrlen)) < 0) {
			perror("[UdpHandler] server - bind() error");
			close(mSockfd);
		}

		mbIsReady = true; // mark as ready
	    return true;
	}

	void UdpHandler::EndSocket() {
		DBG_N("[UdpHandler] Socket deleted");
		close(mSockfd);
	}

	std::string UdpHandler::ReadData() {
		if (!mbIsReady) return NULL;

		bzero(mBuffer, DATA_BUFFER_SIZE);
		char *bufptr = mBuffer;
    	unsigned int buflen = sizeof(mBuffer);

		int n = recvfrom(mSockfd, bufptr, buflen, 0, (struct sockaddr *) &mClientaddr, (unsigned int *) &mClientaddrlen);
        if (n < 0) {
            DBG_E("[UdpHandler] recvfrom() error");
        } else {
            // OKAY
        }

		// printf("Receiver:%s from port %d and address %s\n", bufptr, ntohs(mClientaddr.sin_port), inet_ntoa(mClientaddr.sin_addr));
		return std::string(bufptr);
	}

	void UdpHandler::WriteData(std::string data) {
		if (!mbIsReady) return;

		bzero(mBuffer, DATA_BUFFER_SIZE);
		memcpy(mBuffer, data.c_str(), DATA_BUFFER_SIZE);
		char *bufptr = mBuffer;
    	unsigned int buflen = sizeof(mBuffer);

		int n = sendto(mSockfd, bufptr, buflen, 0, (struct sockaddr *) &mClientaddr, (unsigned int) mClientaddrlen);
        if (n < 0) {
            DBG_E("[UdpHandler] sendto() error");
        } else {
            // printf("UDP Server - sendto() is OK...\n");
        }
	}

	void UdpHandler::WriteData(const char* data) {
		if (!mbIsReady) return;

		bzero(mBuffer, DATA_BUFFER_SIZE);
		memcpy(mBuffer, data, DATA_BUFFER_SIZE);
		char *bufptr = mBuffer;
    	unsigned int buflen = sizeof(mBuffer);

		int n = sendto(mSockfd, bufptr, buflen, 0, (struct sockaddr *) &mClientaddr, (unsigned int) mClientaddrlen);
        if (n < 0) {
            DBG_E("[UdpHandler] sendto() error");
        } else {
            // printf("[UdpHandler] sendto() is OK...\n");
        }
	}

	void UdpHandler::WriteData(int ascii_data) {
		if (!mbIsReady) return;

		bzero(mBuffer, DATA_BUFFER_SIZE);
		mBuffer[0] = ascii_data;
		char *bufptr = mBuffer;
    	unsigned int buflen = sizeof(mBuffer);

		int n = sendto(mSockfd, bufptr, buflen, 0, (struct sockaddr *) &mClientaddr, (unsigned int) mClientaddrlen);
        if (n < 0) {
            DBG_E("[UdpHandler] sendto() error");
        } else {
            // printf("[UdpHandler] sendto() is OK...\n");
        }
	}

	void UdpHandler::WriteData(char buffer[]) {
		if (!mbIsReady) return;

		char *bufptr = buffer;
    	unsigned int buflen = sizeof(buffer);

		int n = sendto(mSockfd, bufptr, buflen, 0, (struct sockaddr *) &mClientaddr, (unsigned int) mClientaddrlen);
        if (n < 0) {
            DBG_E("[UdpHandler] sendto() error");
        } else {
            // printf("[UdpHandler] sendto() is OK...\n");
        }
	}	
} //// namespace Tools ////
