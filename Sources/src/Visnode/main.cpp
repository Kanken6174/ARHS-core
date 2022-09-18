#include "main.hpp"
#include <future>
using namespace psvr;

template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>

auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

int main(int argc, char* argv[])
{
//psvr::Psvr::open();
ui::UiManager::init();
std::future<int> fobj = std::async (cameraManager::init);   //asynchronous camera manager start
ui::UiController::init();
std::future<void> menudraw = std::async (ui::UiDrawer::drawMenu);
ui::UiDrawer::drawStartupSequence();    //show startup sequence while camera manager is starting
menudraw.get();
fobj.get();
cameraManager::runCapture();
SerialPortManager::init();
ui::UiController::exitCalled = false;

int i = 0,count = 1;
_Float64 avgr=0,avgl=0;

while(!ui::UiController::exitCalled){
    #ifdef DBGMODE
    auto start = std::chrono::steady_clock::now();
    #endif
    std::future<void> uiL = std::async (ui::UiDrawer::drawUiL);
    std::future<void> uiR = std::async (ui::UiDrawer::drawUiR);
    uiL.get();
    #ifdef DBGMODE
    auto end1 = since(start).count();
    #endif
    uiR.get();
    #ifdef DBGMODE
    auto end2 = since(start).count();
    #endif
    #ifdef DBGMODE
    std::cout << "Elapsed(ms)=" << end1 << "," << end2 << std::endl;
    if(avgr == 0){
        avgr = end1;
        avgl = end2;
    }else{
        avgr = (avgr+end1)/count;
        avgl = (avgl+end2)/count;
    }

    if(i > 100){
        //std::cout << "\nAVERAGES " << 1000/(avgr*10000) << "," << 1000/(avgl*10000) << std::endl;
        i=0;
    }
    i++;
    count++;
    #endif
}
return 0;
}
