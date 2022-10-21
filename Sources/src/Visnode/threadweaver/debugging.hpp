#include <iostream>
#include <string>

//#define DBGMODE
#define DBGCOMM

#ifdef DBGMODE
#define DEBUG_LOG(x) std::cout << "-DEBUG: " << x << std::endl;
#else
#define DEBUG_LOG(x)
#endif

//#define DBGPRINT(x) do { if (DBGMODE) { std::cerr << x << std::endl; }} while (0)