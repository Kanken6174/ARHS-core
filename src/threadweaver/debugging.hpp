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

#define QU(x) #x
#define QUH(x) QU(x)

#define VERSION_d 0.3
#define VERSION QUH(VERSION_d)

#ifdef DBGMODE
#define DEBUG_LOG(x) std::cout << "-DEBUG: " << x << std::endl;
#else
#define DEBUG_LOG(x)
#endif