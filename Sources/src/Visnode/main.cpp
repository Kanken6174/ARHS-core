#include "main.hpp"
#include <future>
#include <sched.h>
using namespace psvr;

int main(int argc, char* argv[])
{
unsigned num_cpus = std::thread::hardware_concurrency();
cout << num_cpus <<" cores detected" << endl;

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
Threadweaver::osUiDrawerThread = t;

while(!ui::UiController::exitCalled){
    sleep(5);
}

t->join();

return 0;
}