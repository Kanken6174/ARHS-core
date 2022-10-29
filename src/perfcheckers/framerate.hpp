
#include <ctime>
#include <atomic>

class framerateChecker{
    private:
    bool hasBegun = false;

    public:
    std::time_t tBegin, tEnd;
    std::atomic<int> tick,fps = 0;
    long frameCounter = 0;

    void tickBegin();
    void tickUpdate();
};

class fcheckManager{
    public:
    static framerateChecker fcUI;
    static framerateChecker fcShow;
    static framerateChecker fcCam;
};