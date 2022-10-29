#include <thread>
#include <vector>
#include <unistd.h>
#include <filesystem>
#include <sched.h>
#include "./debugging.hpp"

//main thread manager
class Threadweaver{
    public:
    static std::vector<std::thread*> captureThreads;
    static std::thread* hardwareWatcherThread;
    static std::thread* gfxPipelineThread;
    static std::thread* mergerThread;
    static std::thread* osUiDrawerThread;

    static void stick_this_thread_to_core(std::thread* t,int core_id);
};