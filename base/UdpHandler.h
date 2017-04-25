// UDP HANDLER library collection - UdpHandler device class
// Based on MSLRB github project
// 22/04/2017 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 22/04/2017 - 1st release, Basic Function & Constant
//							 MSLRB(Middle Size League Robo Soccer) module
// ...

#ifndef __UDPHANDLER_H__
#define __UDPHANDLER_H__

#include <sys/socket.h> // socket(), bind(), connect() ...
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

#define DATA_BUFFER_SIZE	256

namespace Tools {
	class UdpHandler {
		enum UDP_MODE {
			UDP_SERVER		= 0, //
			UDP_CLIENT		= 1 //
		};

	public:
		UdpHandler(); // this would be as Client
		UdpHandler(unsigned int port); // this would be as Server
		UdpHandler(const char *server, unsigned int port); // this would be as Client
		~UdpHandler();

		bool				Init();
		std::string			ReadData(); // as DATA
		void				WriteData(std::string data);
		void				WriteData(const char* data);
		void				WriteData(int ascii_data);
		void 				WriteData(char buffer[]);
		void				EndSocket();

	private:
		// Member
		bool				mbIsReady;
		unsigned char		mMode;
		int 				mSockfd; // Key
		const char			*mServerIP;
		unsigned int 		mPort;
    	char				mBuffer[DATA_BUFFER_SIZE];

		struct sockaddr_in 	mServeraddr;
		struct sockaddr_in 	mClientaddr;
		int 				mServeraddrlen;
		int 				mClientaddrlen;
	};
} //// namespace Tools ////

#endif /* __UDPHANDLER_H__ */
