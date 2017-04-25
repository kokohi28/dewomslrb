// VISION library collection - Vision device class
//
// 05/10/2014 by Koko Himawan <himawan.koko@gmail.com>
//
// Change Log's :
// 05/10/2014 - 1st release, Basic interfacing
//							 RSHL(Robo Soccer Humanoid Leauge) module
//							 Ball Tracking(based colour tracking), get from http://www.aishack.in/
//							 Face detection(based haar cascade method)
// 22/04/2017 : Edit code style
// ...

#ifndef __VISION_H__
#define __VISION_H__

#include "opencv2/opencv.hpp"
#include <iostream>

#include "Uart.h"

#define CV_USE_FACE_DETECTION		0 // set 0 to disable, 1 enable

namespace Tools {
	class Vision {
	public:
		enum OUTPUT_MODE {
			CONSOLE				= 0,
			GUI_NORMAL			= 1,
			GUI_BGR2HSV			= 2,
			GUI_RGB2HSV			= 3,
			GUI_THRES			= 4,
			GUI_2BIT			= 5,
			OUTPUT_MODE_COUNT	= 6
		};

		enum WINDOW_SIZE {
			WINDOW_TINY			= 0,
			WINDOW_SMALL		= 1,
			WINDOW_NORMAL		= 2,
			WINDOW_LARGE		= 3,
			WINDOW_SIZE_COUNT	= 4
		};

	private:
		IplImage*					m_Frame;
		CvCapture*					m_Capture;

	#if CV_USE_FACE_DETECTION
		CvHaarClassifierCascade*	m_Cascade; // face detection
		CvMemStorage*				m_Storage;
	#endif

		OUTPUT_MODE					m_OutMode;
		unsigned char				m_OutModeIndex;
		unsigned char				m_WindowSizeIndex;

		typedef struct {
			uint16_t x;
			uint16_t y;
		} Point;
		Point						m_WindowsSize[WINDOW_SIZE_COUNT - 1];
		Point						m_ObjectLocation;

		bool						InitCVCapture(uint8_t device, Point size);
		void						InitWindowSize();
		IplImage*					GetHSVImage(IplImage* img, int16_t mode);
		IplImage* 					GetThresholdedImage(IplImage* img);

	#if CV_USE_FACE_DETECTION
		IplImage*					DetectFaces(IplImage *img);
	#endif

		bool						UpdateMode();
		bool						UpdateFrame();

	public:
		Vision();
		~Vision();

		bool						Init();
		bool						Update();
		void						GetObjectLocation(uint16_t &x, uint16_t &y);
		void 						SaveCapturedFrame(std::string fileName);
		void						SendViaUart(int delay, Tools::Uart* comm);
	};

} //// namespace Tools ////

#endif /* __VISION_H__ */
