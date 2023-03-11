#include <iostream>
#include <string>
//#include "../model/perfcheckers/framerate.hpp"

//#define DBGMODE
#define DBGCOMM
#define OGLWIN
#define GFXCORE 0
#define DISPLAYCORE 1
#define CAMCORE 2
#define MERGECORE 3

#define FPS_LIMIT_MERGE 60
#define FPS_LIMIT_DRAW 30
#define FPS_LIMIT_DISPLAY 60

#define FPS_LIMIT_PSEYE 15  //increments of 15, valid values: 0-15-30-60

#define DEFAULT_UI_WINDOW_AMOUNT 1 // 2 windows, one for each eye
#define DEFAULT_UI_OFFSET_X 1080   // 1080
#define DEFAULT_UI_OFFSET_Y 0
#define DEFAULT_UI_SIZE_X 1920 // psvr is 960x1080 per eye
#define DEFAULT_UI_SIZE_Y 1080

#define QU(x) #x
#define QUH(x) QU(x)

#define VERSION_d 0.5
#define VERSION QUH(VERSION_d)

#ifdef DBGMODE
#define DEBUG_LOG(x) std::cout << "-DEBUG: " << x << std::endl;
#else
#define DEBUG_LOG(x)
#endif