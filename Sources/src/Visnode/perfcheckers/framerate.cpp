#include "framerate.hpp"

void framerateChecker::tickBegin(){
    if(hasBegun) return;
    tBegin = std::time(0);
    hasBegun = true;
    tick = 0;
    fps = 0;
}

void framerateChecker::tickUpdate(){
    frameCounter++;
    tEnd = std::time(0) - tBegin;

    if(tEnd - tick < 1) return;
    tick++;
    fps = frameCounter;
    frameCounter = 0;
}