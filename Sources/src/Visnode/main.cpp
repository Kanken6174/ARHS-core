#include "main.hpp"
#include <future>
using namespace psvr;

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
while(!ui::UiController::exitCalled){
    std::future<void> uiL = std::async (ui::UiDrawer::drawUiL);
    std::future<void> uiR = std::async (ui::UiDrawer::drawUiR);
    uiL.get();
    uiR.get();
}
return 0;
}
