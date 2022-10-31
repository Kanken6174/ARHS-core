#pragma once
#include <thread>
#include <vector>
#include <unistd.h>
#include <filesystem>
#include <sched.h>
#include "./debugging.hpp"

//main thread manager
class Threadweaver{
    public:

    static void stick_this_thread_to_core(std::thread* t,int core_id);
    static int getCoreCount();
};