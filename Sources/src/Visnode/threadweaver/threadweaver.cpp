#include "./threadweaver.hpp"

std::vector<std::thread*> Threadweaver::captureThreads;
std::thread* Threadweaver::hardwareWatcherThread;
std::thread* Threadweaver::osUiDrawerThread;