#include <iostream>
#include <string>

//#define DBGMODE
#define DBGCOMM
#define OGLWIN
#define GFXCORE 0
#define DISPLAYCORE 1
#define CAMCORE 2
#define HWCORE 3

#ifdef DBGMODE
#define DEBUG_LOG(x) std::cout << "-DEBUG: " << x << std::endl;
#else
#define DEBUG_LOG(x)
#endif