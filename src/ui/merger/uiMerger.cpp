#include "../_ui.hpp"

UMat ui::UiMerger::output;
std::mutex ui::UiMerger::outputLock;

namespace ui
{
    void UiMerger::runMerge()
    {
        try
        {
            cout << "starting ui merger thread" << endl;
            ui::UiController::exitCalled = false;
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            while (true)
            {
                begin = std::chrono::steady_clock::now();
                DEBUG_LOG("drawing");
                ui::UiMerger::mergeUI();
                end = std::chrono::steady_clock::now();
                std::this_thread::sleep_for (std::chrono::milliseconds((1000/FPS_LIMIT_MERGE)-std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count()));
            }
        }
        catch (...)
        {
            cerr << "\033[1;31m caught mergeUI thread exception \033[0m" << endl;
            exit(1);
        }
    }

    void UiMerger::mergeUI()
    {
        DEBUG_LOG("\nBegan new pipeline cycle-------------------------------")
        fcheckManager::fcMergeUI.tickBegin();
        UMat UiMat = UiSupport::prepareUiMat(); // prepare black background 960*1080
        DEBUG_LOG("prepared UI mat")
        cameraManager::accessLocks[0]->lock();         // lock the capture access
        UMat cameraFrame = cameraManager::captures[0]; // retreive latest camera frame
        cameraManager::accessLocks[0]->unlock();       // unlock capture access
        DEBUG_LOG("retreived camera frame")
        if (cameraFrame.rows <= 0 || cameraFrame.cols <= 0)
            return;                                     // check for empty frame
        cameraFrame = UiSupport::resizeIn(cameraFrame); // resize the frame to the standard format
        DEBUG_LOG("resized camera frame")
        // Copy the frame in the center of the background
        cameraFrame.copyTo(UiMat(cv::Rect((UiMat.cols / 2) - (cameraFrame.cols / 2), (UiMat.rows / 2) - (cameraFrame.rows / 2), cameraFrame.cols, cameraFrame.rows)));
        DEBUG_LOG("copied camera frame")
        if (UiController::showMenu)
        {
            UiDrawer::outputLock.lock();
            // UiMat = OverlayBlackMask(UiMat, OsMat, ui::UiController::menuPos.x,ui::UiController::menuPos.y);         //add the OS ui overlay
            UiMat = UiSupport::OverlayBlackMask(UiMat, UiDrawer::output);
            UiDrawer::outputLock.unlock();
        }
        DEBUG_LOG("drawn menu")
        UMat finished = UiSupport::makeMatStereo(UiMat);
        DEBUG_LOG("concated mats")

        UiManager::accessLocks.at(0)->lock();
        UiManager::managedUIs[0]->drawSurface = finished; // write the final image to the psvr UI buffer
        UiManager::accessLocks.at(0)->unlock();
        fcheckManager::fcMergeUI.tickUpdate();
    }
}