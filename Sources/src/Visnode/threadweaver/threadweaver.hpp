#include <thread>
#include <vector>
#include "./debugging.hpp"

//main thread manager
class Threadweaver{
    public:
    static std::vector<std::thread*> captureThreads;
    static std::thread* hardwareWatcherThread;
    static std::thread* osUiDrawerThread;
};