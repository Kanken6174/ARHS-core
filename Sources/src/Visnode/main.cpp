#include "main.hpp"
#include <future>
#include <sched.h>
using namespace psvr;

int main(int argc, char* argv[])
{
unsigned num_cpus = std::thread::hardware_concurrency();
cout << num_cpus <<" cores detected" << endl;
std::cout << cv::getBuildInformation() << std::endl;


//psvr::Psvr::open();
ui::UiManager::init();
std::future<int> fobj = std::async (cameraManager::init);   //asynchronous camera manager start
ui::UiController::init();
ui::UiController::runIntro = true;
std::future<void> menudraw = std::async (ui::UiDrawer::drawMenu);
ui::UiDrawer::drawStartupSequence();    //show startup sequence while camera manager is starting
menudraw.get();
fobj.get();

cameraManager::runCapture();
SerialPortManager::init();
ui::UiController::exitCalled = false;
ui::UiController::runIntro = false;

std::thread* t = new std::thread(ui::UiDrawer::runDrawUi);
Threadweaver::stick_this_thread_to_core(t,1);
Threadweaver::gfxPipelineThread = t;

while(!ui::UiController::exitCalled){
    sleep(5);
}

Threadweaver::gfxPipelineThread->join();

return 0;
}