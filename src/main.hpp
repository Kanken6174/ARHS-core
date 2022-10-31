#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <future>
#include <sched.h>

#include "./hardware/hw/serial.hpp"

class topLevelManager{
    public:
    void init();
    private:
    void detectHWAndConfig();
    void setupThreads();
};