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

#include "Vision.h"
#include "Tools.h"
#include "ConfigParser.h"
#include <stdio.h>

#define WINDOW_NAME					"DEWO"
#define FOLDER_TO_LOCAL_SAVE		"captured/" // make sure folder is exist before store image

#define USING_THIS_PRE_CONFIG		0 // 0 for load from Config file

#if CV_USE_FACE_DETECTION
	#define HAAR_CASCADE_FILE 		"haarcascade_frontalface_alt.xml"
#endif

#if USING_THIS_PRE_CONFIG
	#define	THRES_START_H			11
	#define	THRES_START_S			140
	#define	THRES_START_V			100

	#define	THRES_END_H				16
	#define	THRES_END_S				230
	#define	THRES_END_V				255

	#define PRE_OUT_MODE			GUI_NORMAL
	#define PRE_OUT_WINDOW			WINDOW_SMALL
	#define SEND_DATA_MODE			0 // 0 = Grayscale, 1 = RGB
#endif

namespace Tools {
	Vision::Vision():
		m_Frame(NULL)
		, m_Capture(NULL)

	#if USING_THIS_PRE_CONFIG
		, m_OutMode(PRE_OUT_MODE)
		, m_OutModeIndex((unsigned char) PRE_OUT_MODE)
		, m_WindowSizeIndex((unsigned char) PRE_OUT_WINDOW)
	#endif

	#if CV_USE_FACE_DETECTION
		, m_Cascade(NULL)
		, m_Storage(NULL)
	#endif
	{

	}

	Vision::~Vision() {
		DBG_W("[Vision] Delete Resources");

		cvReleaseCapture(&m_Capture);
		m_Capture = NULL;
		cvReleaseImage(&m_Frame);
		m_Frame = NULL;

	#if CV_USE_FACE_DETECTION
		cvReleaseHaarClassifierCascade(&m_Cascade);
		m_Cascade = NULL;
		cvReleaseMemStorage(&m_Storage);
		m_Storage = NULL;
	#endif
	}

	bool Vision::Init() {
		DBG_I("[Vision] Init");

		InitWindowSize();

	#if USING_THIS_PRE_CONFIG
		// Already init's @constructor
	#else
		unsigned char mode, size, temp1, temp2, temp3, temp4, temp5, temp6;
		Tools::ConfigParser::GetInstance()->GetVisionParameter(mode, size, temp1, temp2, temp3, temp4, temp5, temp6);

		m_OutMode = (OUTPUT_MODE) mode;
		m_OutModeIndex = mode;
		m_WindowSizeIndex = (WINDOW_SIZE) size;
	#endif

		if (!InitCVCapture(0, m_WindowsSize[(WINDOW_SIZE) m_WindowSizeIndex]))
			return false;

		m_ObjectLocation.x = 0;
		m_ObjectLocation.y = 0;

	#if CV_USE_FACE_DETECTION
		m_Cascade = (CvHaarClassifierCascade*)cvLoad(filename, 0, 0, 0);
		m_Storage = cvCreateMemStorage(0);
	#endif

		return true;
	}

	void Vision::InitWindowSize() { // Depend's on hardware
		// Logitech Camera Resolution Support
		// 160 x 90		// 160 x 120	// 176 x 144 	// 320 x 240	// 320 x 180
		// 352 x 288 	// 432 x 240	// 640 x 480	// 640 x 360	// 800 x 448
		// 800 x 600	// ...

		// Tiny
		m_WindowsSize[WINDOW_TINY].x	= 160;
		m_WindowsSize[WINDOW_TINY].y	= 120;

		// Small
		m_WindowsSize[WINDOW_SMALL].x	= 320;
		m_WindowsSize[WINDOW_SMALL].y	= 240;

		// Normal
		m_WindowsSize[WINDOW_NORMAL].x	= 640;
		m_WindowsSize[WINDOW_NORMAL].y	= 480;

		// Large
		m_WindowsSize[WINDOW_LARGE].x	= 800;
		m_WindowsSize[WINDOW_LARGE].y	= 600;

	}

	bool Vision::Update() {
		if (!UpdateMode()) return false;

		if (!UpdateFrame()) return false;

		return true;
	}

	void Vision::GetObjectLocation(uint16_t &x, uint16_t &y) {
		x = m_ObjectLocation.x;
		y = m_ObjectLocation.y;
	}

	bool Vision::UpdateMode() {
		int c = cvWaitKey(1); // Just worked when used cvWindow
		switch(c) {
			case KEY_Z_SMALL:
				m_OutModeIndex++;
				if (m_OutModeIndex > (unsigned char) GUI_2BIT) {
					m_OutModeIndex = (unsigned char) CONSOLE;
				}
				m_OutMode = (OUTPUT_MODE) m_OutModeIndex;

				break;
			case KEY_X_SMALL:
				m_WindowSizeIndex++;
				if (m_WindowSizeIndex > (unsigned char) WINDOW_NORMAL) { // Just use tiny-small-normal window
					m_WindowSizeIndex = (unsigned char) WINDOW_TINY;
				}

				if (!InitCVCapture(0, m_WindowsSize[(WINDOW_SIZE) m_WindowSizeIndex]))
					return false;

				break;
			case KEY_C_SMALL:
				SaveCapturedFrame("Captured.jpg");
				break;
			case KEY_ESC:
				return false; // Quit Confirmed
				break;

			default:
				break;
		}

		return true;
	}

	bool Vision::UpdateFrame() {
		m_Frame = cvQueryFrame(m_Capture);
		if (!m_Frame) return false; // Fail query frame

		// printf("Mode Vision:%d\n", m_OutMode);
		switch(m_OutMode) {
			case GUI_NORMAL: {
				cvAddS(m_Frame, cvScalar(50,50,50), m_Frame);
				cvShowImage(WINDOW_NAME, m_Frame);
			}
				break; // JUST Normal frame

			case GUI_BGR2HSV: {
				IplImage* imgHSV = GetHSVImage(m_Frame, CV_BGR2HSV);
				cvShowImage(WINDOW_NAME, imgHSV);
				cvReleaseImage(&imgHSV); // MUST release
			}
				break; // BGR to HSV frame

			case GUI_RGB2HSV: {
				IplImage* imgHSV = GetHSVImage(m_Frame, CV_RGB2HSV);
				cvShowImage(WINDOW_NAME, imgHSV);
				cvReleaseImage(&imgHSV); // MUST release
			}
				break; // RGB to HSV frame

			case GUI_THRES: {
				IplImage* imgThres = GetThresholdedImage(m_Frame);
				cvShowImage(WINDOW_NAME, imgThres);
				cvReleaseImage(&imgThres); // MUST release
			}
				break; // Thresholded frame

			case GUI_2BIT: {
				DBG_I("[Vision] 2 bit mode!");
			}
				break;

			case CONSOLE: {
				IplImage* imgThres = GetThresholdedImage(m_Frame);
				cvMorphologyEx(imgThres , imgThres , NULL, NULL, CV_MOP_OPEN, 1);
				CvMoments* moments = (CvMoments*) malloc(sizeof(CvMoments));
				cvMoments(imgThres, moments, 1);

				double moment10 = cvGetSpatialMoment(moments, 1, 0);
				double moment01 = cvGetSpatialMoment(moments, 0, 1);
				double area = cvGetCentralMoment(moments, 0, 0);

				static int posX = 0;
				static int posY = 0;

				int lastX = posX;
				int lastY = posY;

				posX = moment10 / area;
				posY = moment01 / area;

				if( (posX > 0 && posX < (m_WindowsSize[(WINDOW_SIZE) m_WindowSizeIndex].x + 1)) &&
				    (posY > 0 && posY < (m_WindowsSize[(WINDOW_SIZE) m_WindowSizeIndex].y + 1)) ) {
					// printf("[Vision] Tracked:%d, %d\n", posX, posY);
					m_ObjectLocation.x = posX;
					m_ObjectLocation.y = posY;
				}  else {
					m_ObjectLocation.x = 0;
					m_ObjectLocation.y = 0;
				}

				// cvShowImage(WINDOW_NAME, imgThres);

				cvReleaseImage(&imgThres);
				delete moments;
			}
				break; // Simple coordinat frame

			default:
				break;
		}

		return true;
	}

	bool Vision::InitCVCapture(uint8_t device, Point size) {
		if (m_Capture) {
			DBG_W("[Vision] Capture already created, DELETE one!");
			cvReleaseCapture(&m_Capture);
			m_Capture = NULL;
		}

		m_Capture = cvCaptureFromCAM(device);
		if (!m_Capture) {
			DBG_E("[Vision] Can't create capture!");
			return false;
		}

		cvSetCaptureProperty(m_Capture, CV_CAP_PROP_FRAME_WIDTH, size.x);
		cvSetCaptureProperty(m_Capture, CV_CAP_PROP_FRAME_HEIGHT, size.y);

		return true;
	}

	void Vision::SaveCapturedFrame(std::string fileName) {
		std::string path = FOLDER_TO_LOCAL_SAVE + fileName;
		printf("[Vision] Save as: %s\n", path.c_str());
		cvSaveImage(path.c_str(), m_Frame);
		DBG_I("[Vision] Save done!");
	}

	IplImage* Vision::GetHSVImage(IplImage* img, int16_t mode) {
		IplImage* imgHSV = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
		cvCvtColor(img, imgHSV, mode);
		return imgHSV;
	}

	IplImage* Vision::GetThresholdedImage(IplImage* img) {
		IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
		cvCvtColor(img, imgHSV, CV_BGR2HSV);
		IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);

		unsigned char thresH1, thresS1, thresV1;
		unsigned char thresH2, thresS2, thresV2;
	#if USING_THIS_PRE_CONFIG
		thresH1 = THRES_START_H;
		thresS1 = THRES_START_S;
		thresV1 = THRES_START_V;
		thresH2 = THRES_END_H;
		thresS2 = THRES_END_S;
		thresV2 = THRES_END_V;
	#else
		unsigned char temp1, temp2;
		Tools::ConfigParser::GetInstance()->GetVisionParameter(temp1, temp2, thresH1, thresS1, thresV1, thresH2, thresS2, thresV2);
	#endif

		// printf("Thres:%d %d %d %d %d %d\n", thresH1, thresS1, thresV1, thresH2, thresS2, thresV2);
		cvInRangeS(imgHSV, cvScalar(thresH1, thresS1, thresV1), cvScalar(thresH2, thresS2, thresV2), imgThreshed);
		cvReleaseImage(&imgHSV);
		return imgThreshed;
	}

#if CV_USE_FACE_DETECTION
	IplImage* Vision::DetectFaces(IplImage *img) {
		// Detect faces
		CvSeq *faces = cvHaarDetectObjects(img, m_Cascade, m_Storage,
							1.1, 3, 0 /*CV_HAAR_DO_CANNY_PRUNNING*/,
							cvSize(40, 40));

		// For each face found, draw a red box
		for (int i = 0; i < ( faces ? faces->total : 0 ); i++) {
			CvRect *rect = (CvRect*)cvGetSeqElem(faces, i);
			cvRectangle(img, cvPoint(rect->x, rect->y),
				cvPoint(rect->x + rect->width, rect->y + rect->height),
				CV_RGB(255, 0, 0), 1, 8, 0);
		}
		return img;
	}
#endif

	// Send Via Uart
	void Vision::SendViaUart(int delay, Tools::Uart* comm) {
		DBG_I("[Vision] Start Send Data");

		int mode = 0;
	#if USING_THIS_PRE_CONFIG
		mode = SEND_DATA_MODE;
	#else
		unsigned char temp1;
		int temp2, temp3;
		Tools::ConfigParser::GetInstance()->GetSendImageUartParameter(temp1, temp2, temp3); // temp1 as mode
		mode = (int) temp1;
	#endif

		CvScalar temp;
		int data;
		int sizeY = (int) m_WindowsSize[(WINDOW_SIZE) m_WindowSizeIndex].y;
		int sizeX = (int) m_WindowsSize[(WINDOW_SIZE) m_WindowSizeIndex].x;
		for (register int x = (sizeY / 2) - 100; x < (sizeY / 2) + 100; x++) {
			comm->Send(255); // flag for new line
			for (int y = (sizeX / 2) - 100; y < (sizeX / 2) + 100; y++) { // Image
				temp = cvGet2D(m_Frame, x, y);

				if (mode == 0) { // Grayscale
					data = (int) ((temp.val[2] + temp.val[1] + temp.val[0]) / 3);
					if (data == 255)
						data = 254;
					comm->Send(data);
				} else {			// RGB
					data = temp.val[2]; // R
					if (data == 255)
						data = 254;
					comm->Send(data);

					data = temp.val[1]; // G
					if (data == 255)
						data = 254;
					comm->Send(data);

					data = temp.val[0]; // B
					if (data == 255)
						data = 254;
					comm->Send(data);
				}

				Tools::SimpleWait(delay); // Delay
			}
		}

		DBG_I("[Vision] Finish Send Data");
	}

} //// namespace Tools ////
