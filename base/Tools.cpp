// Standard Tools - Namespace Tools
// 13/09/2014 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 13/09/2014 - 1st release, Basic Function & Constant
//							 RSHL(Robo Soccer Humanoid Leauge) module
// 22/04/2017 - Edit code style
// ...

#include "Tools.h"
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <ctime>

namespace Tools {
	// SIMPLE Empty Loop for Delay
	void SimpleWait(long _x1000) {
		for (long i = 0; i <= (1000 * _x1000); i++);
	}

	// Getche() like in Conio.h WIN32
	int Getche() {
		struct termios oldattr, newattr;
		int ch;
		tcgetattr(STDIN_FILENO, &oldattr);
		newattr = oldattr;
		newattr.c_lflag &= ~(ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
		ch = getchar();
		tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
		return ch;
	}

	// Getch() like in Conio.h WIN32
	char Getch() {
		char buf = 0;
		struct termios old = {0};
		if (tcgetattr(0, &old) < 0) {
			perror("tcsetattr()");
		}

		old.c_lflag &= ~ICANON;
		old.c_lflag &= ~ECHO;
		old.c_cc[VMIN] = 1;
		old.c_cc[VTIME] = 0;
		if (tcsetattr(0, TCSANOW, &old) < 0) {
			perror("tcsetattr ICANON");
		}
		if (read(0, &buf, 1) < 0) {
			perror("read()");
		}
		old.c_lflag |= ICANON;
		old.c_lflag |= ECHO;
		if (tcsetattr(0, TCSADRAIN, &old) < 0) {
			perror("tcsetattr ~ICANON");
		}
		return (buf);
	}

	// Keyboard Hit
	bool KeyHit() {
		struct termios oldt, newt;
		int ch;
		int oldf;

		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
		fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

		ch = getchar();

		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, oldf);

		if (ch != EOF) {
			ungetc(ch, stdin);
			return true;
		}

		return false;
	}

	// Time utility
	int Time::GetYear() {
		time_t t = time(0);
		struct tm * now = localtime(&t);
		return (now->tm_year + 1900);
	}

	int Time::GetMonth() {
		time_t t = time(0);
		struct tm * now = localtime(&t);
		return (now->tm_mon + 1);
	}

	int Time::GetDate() {
		time_t t = time(0);
		struct tm * now = localtime(&t);
		return (now->tm_mday);
	}

	int Time::GetHour() {
		time_t t = time(0);
		struct tm * now = localtime(&t);
		return (now->tm_hour);
	}

	int Time::GetMinute() {
		time_t t = time(0);
		struct tm * now = localtime(&t);
		return (now->tm_min);
	}

	int Time::GetSecond() {
		time_t t = time(0);
		struct tm * now = localtime(&t);
		return (now->tm_sec);
	}

	std::string Time::GetDenseFormatTime() {
		int num;
		char temp[4];
		std::string timeStr, str;

		// Year
		num = GetYear();
		sprintf(temp, "%d", num);
		timeStr = temp;
		// Month
		num = GetMonth();
		if (num < 10) {
			sprintf(temp, "0%d", num);
		} else {
			sprintf(temp, "%d", num);
		}

		timeStr += temp;
		// Date
		num = GetDate();
		if (num < 10) {
			sprintf(temp, "0%d", num);
		} else {
			sprintf(temp, "%d", num);
		}
		timeStr += temp;
		timeStr += "_";

		// Hour
		num = GetHour();
		if (num < 10) {
			sprintf(temp, "0%d", num);
		} else {
			sprintf(temp, "%d", num);
		}
		timeStr += temp;
		// Minute
		num = GetMinute();
		if (num < 10) {
			sprintf(temp, "0%d", num);
		} else {
			sprintf(temp, "%d", num);
		}
		timeStr += temp;
		// Second
		num = GetSecond();
		if (num < 10) {
			sprintf(temp, "0%d", num);
		} else {
			sprintf(temp, "%d", num);
		}
		timeStr += temp;

		return timeStr;
	}

} //// namespace Tools ////
