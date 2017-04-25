// TCP HANDLER library collection - TcpHandler device class
// Based on MSLRB github project
// 22/04/2017 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/04/2017 - 1st release, Basic Function & Constant
//							 MSLRB(Middle Size League Robo Soccer) module
// ...

#ifndef __TCPHANDLER_H__
#define __TCPHANDLER_H__

#include <sys/socket.h> // socket(), bind(), connect() ...
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

#define DATA_BUFFER_SIZE	256

namespace Tools {
	class TcpHandler {
	public:
		TcpHandler();
		TcpHandler(const char *server, unsigned int port);
		~TcpHandler();

		bool				Init();
		int					ReadData(); // as ASCII CODE
		void				WriteData(std::string data);
		void				WriteData(int ascii_data);
		void				EndSocket();

	private:
		// Member
		bool				mbIsReady;
		int 				mSockfd; // Key
		const char			*mServerIP;
		unsigned int 		mPort;
    	char				mBuffer[DATA_BUFFER_SIZE];
	};
} //// namespace Tools ////

#endif /* __TCPHANDLER_H__ */
