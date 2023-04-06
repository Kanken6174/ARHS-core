#include "main.hpp"

using namespace psvr;

topLevelManager::topLevelManager()
{
    try
    {
        detectHWAndConfig();
        setupThreads();
        std::cout << "Config finished, main thread now sleeping" << endl;
        while (true)
        {
            sleep(1);
        }
    }
    catch (...)
    {
        cerr << "caught main thread exception" << endl;
    }

    DEBUG_LOG("Exitted sleep while")
    //Threadweaver::gfxPipelineThread->join();
}

void topLevelManager::detectHWAndConfig(){
    char tmp[256];
    getcwd(tmp, 256);
    std::cout << "Current working directory: " << tmp << std::endl;

    unsigned num_cpus = std::thread::hardware_concurrency();
    cout << num_cpus << " cores detected" << endl;
    std::cout << cv::getBuildInformation() << std::endl;
}

void topLevelManager::setupThreads(){
    localPipeline = new Pipeline();


    #pragma region deprecated
    {
    /*
        // psvr::Psvr::open();
        ui::UiManager::init();
        InputManager::init();
        std::future<int> fobj = std::async(cameraManager::init); // asynchronous camera manager start
        ui::UiController::init();
        ui::UiController::runIntro = true;
        std::future<void> menudraw = std::async(ui::UiDrawer::drawMenu);
        sleep(3);   //waiting for camera pipeline to setup
        menudraw.wait();
        fobj.get();

        cameraManager::runCapture();

        ui::UiController::exitCalled = false;
        ui::UiController::runIntro = false;

        std::thread *t = new std::thread(ui::UiDrawer::runDrawMenu);
        Threadweaver::stick_this_thread_to_core(t, GFXCORE);
        Threadweaver::gfxPipelineThread = t;
        sleep(1);   //waiting for first menu drawing execution (or else we get an infinite mutex lock)
        std::thread *t2 = new std::thread(ui::UiMerger::runMerge);
        Threadweaver::stick_this_thread_to_core(t2,MERGECORE);
        Threadweaver::mergerThread = t2;
    */
    }
   #pragma endregion deprecated
}