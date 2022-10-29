#include "../_ui.hpp"
UMat ui::UiDrawer::output;
std::mutex ui::UiDrawer::outputLock;
framerateChecker* ui::UiDrawer::fpsCounter = new framerateChecker();

namespace ui{

    void UiDrawer::drawStartupSequence(){
        cout << "opening external ressources" << endl;
        VideoCapture cap("./media/hud_startup.gif");
        cout << "opened video"<< endl;
        if(!cap.isOpened()){
            cout << "failed to open hud start media" << endl;
            return;
        }
        UMat frame;
        UMat finished;
        #ifdef OGLWIN
        cv::ogl::Texture2D frameOGL = Texture2D();
        #endif
        while(cap.read(frame))
        {
            finished = UiSupport::makeMatStereo(frame);
        #ifdef OGLWIN
            frameOGL.copyFrom(finished);
            cv::imshow(ui::UiManager::managedUIs.at(0)->myWindow, frameOGL);
        #else
            cv::imshow(ui::UiManager::managedUIs.at(0)->myWindow, finished);
        #endif
            if(waitKey(30) >= 0) break;
        }
        cap.release();
    }

    void UiDrawer::drawMenu(){
        try{
        fcheckManager::fcDrawMenu.tickBegin();
        int& wd = UiController::menuSize.width;
        int& he = UiController::menuSize.height;
        unsigned int stackerIndex = 0;
        UMat MenuMat(cv::Size(wd, he), CV_8UC3,Scalar(0,0,0));
        cv::rectangle(MenuMat, cv::Rect2i(0,0,wd, he), Scalar(255,0,0), 5, 8, 0);
        ui::UiController::update();
        cv::putText(MenuMat, UiController::menuTitle, Point2i(5,stackerIndex+=20), HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255), 1, 8, false);
        for(std::map<std::string,std::function<void()>>::iterator iter = UiController::menuItems.begin(); iter != UiController::menuItems.end(); ++iter)
        {
        std::string str =  iter->first;
        cv::putText(MenuMat, str, Point2i(5,stackerIndex+=20), HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255), 1, 8, false);
        }
        int mFps,uiFps,Drawfps,camFPS = 0;
        mFps = fcheckManager::fcMergeUI.fps;
        uiFps = fcheckManager::fcDrawMenu.fps;
        Drawfps = fcheckManager::fcShow.fps;
        camFPS = fcheckManager::fcCam.fps;
        cv::putText(MenuMat, cv::format("Eps Ui drawer: %d", uiFps), Point2i(5,stackerIndex+=20), HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255), 1, 8, false);
        cv::putText(MenuMat, cv::format("Eps Ui merger: %d", mFps), Point2i(5,stackerIndex+=20), HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255), 1, 8, false);
        cv::putText(MenuMat, cv::format("Eps imshow: %d", Drawfps), Point2i(5,stackerIndex+=20), HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255), 1, 8, false);
        cv::putText(MenuMat, cv::format("Eps Camera 0: %d", camFPS), Point2i(5,stackerIndex+=20), HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255), 1, 8, false);
        
        cv::rectangle(MenuMat, cv::Rect2i(0,((20*ui::UiController::selectedIndex)+20)+5,wd, 20), Scalar(200,0,0), 3, 8, 0);
        outputLock.lock();
        output = MenuMat;
        outputLock.unlock();
        } catch(...){
            cerr << "\033[1;31m caught DrawUi::drawMenu thread exception \033[0m" << endl;
            exit(1);
        }
        fcheckManager::fcDrawMenu.tickUpdate();
    }

    void UiDrawer::runDrawMenu(){
        try{
        cout << "starting ui drawer thread" << endl;
        ui::UiController::exitCalled = false;
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        while(true){
            DEBUG_LOG("drawing");
            begin = std::chrono::steady_clock::now();
            ui::UiDrawer::drawMenu();
            end = std::chrono::steady_clock::now();
            std::this_thread::sleep_for (std::chrono::milliseconds((1000/FPS_LIMIT_DRAW)-std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count()));
        }
        } catch(...){
            cerr << "\033[1;31m caught DrawUi thread exception \033[0m" << endl;
            exit(1);
        }
    }
}
