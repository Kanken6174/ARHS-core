#include <iostream>
#include <string>

//#define DBGMODE
#define DBGCOMM
#define OGLWIN

#ifdef DBGMODE
#define DEBUG_LOG(x) std::cout << "-DEBUG: " << x << std::endl;
#else
#define DEBUG_LOG(x)
#endif