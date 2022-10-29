#include <iostream>
#include <string>
#include "../perfcheckers/framerate.hpp"

//#define DBGMODE
#define DBGCOMM
//#define OGLWIN
#define GFXCORE 0
#define DISPLAYCORE 1
#define CAMCORE 2
#define MERGECORE 3

#define FPS_LIMIT_MERGE 160
#define FPS_LIMIT_DRAW 160

#define FPS_LIMIT_PSEYE 90

#define QU(x) #x
#define QUH(x) QU(x)

#define VERSION_d 0.4
#define VERSION QUH(VERSION_d)

#ifdef DBGMODE
#define DEBUG_LOG(x) std::cout << "-DEBUG: " << x << std::endl;
#else
#define DEBUG_LOG(x)
#endif