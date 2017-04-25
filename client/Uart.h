// UART Serial comm library collection - uart device class
// 05/10/2014 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 05/10/2014 - 1st release, Basic interfacing
//							 RSHL(Robo Soccer Humanoid Leauge) module
// 22/04/2017 : Edit code style
// ...

#ifndef __UART_H__
#define __UART_H__

#include "Tools.h"

namespace Tools {
	class Uart {
	public:
		Uart();
		~Uart();

	private:
		int*				m_Comm;

		bool				Open(int &uart, const char* modem, int baudrate);
		void				Close(int &uart);

	public:
		void				Send(int data);
		void				Send(int data, int uart);
		void				SendDigit(long data, int length, int uart, int delay);
		int					Read(int uart);

		void				Test();
		void				Test(int uart);
		int					GetComm(LEVEL level);
		bool 				OpenAvailableComm();
		void				CloseAvailableComm();

	};

} //// namespace Tools ////

#endif /* __UART_H__ */
