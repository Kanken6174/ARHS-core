
#include <ctime>

class framerateChecker{
    private:
    bool hasBegun = false;

    public:
    std::time_t tBegin, tEnd;
    int tick, fps = 0;
    long frameCounter = 0;

    void tickBegin();
    void tickUpdate();
};