#include "_ui.hpp"
UMat ui::UiDrawer::OverlayMat;
UMat ui::UiDrawer::OsMat;   //drawn on certain events
std::mutex ui::UiDrawer::OsMatLock;

            //UiMat = prepareUiMat();
            //surface.copyTo(UiMat(cv::Rect((UiMat.cols/2)-(surface.cols/2),(UiMat.rows/2)-(surface.rows/2),surface.cols, surface.rows)));
            //UiMat = OverlayBlackMask(UiMat, overlay);

namespace ui{
    //draws the UI for the left screen of the psvr
    void UiDrawer::drawUi(){
            UMat UiMat = prepareUiMat();               //prepare black background 960*1080
            DEBUG_LOG("prepared UI mat")
            cameraManager::accessLocks[0]->lock();      //lock the capture access
            UMat cameraFrame = cameraManager::captures[0];   //retreive latest camera frame
            cameraManager::accessLocks[0]->unlock();    //unlock capture access
            DEBUG_LOG("retreived camera frame")
            if(cameraFrame.rows <= 0 || cameraFrame.cols <= 0) return;  //check for empty frame
            cameraFrame = resizeIn(cameraFrame);                //resize the frame to the standard format
            DEBUG_LOG("resized camera frame")
            //Copy the frame in the center of the background
            cameraFrame.copyTo(UiMat(cv::Rect((UiMat.cols/2)-(cameraFrame.cols/2),(UiMat.rows/2)-(cameraFrame.rows/2),cameraFrame.cols, cameraFrame.rows)));
            DEBUG_LOG("copied camera frame")
            UiMat = OverlayBlackMask(UiMat, OverlayMat);    //add the fixed overlay
            DEBUG_LOG("overlayed camera frame")
            if(UiController::showMenu){
                UiDrawer::drawMenu();
                OsMatLock.lock();
                //UiMat = OverlayBlackMask(UiMat, OsMat, ui::UiController::menuPos.x,ui::UiController::menuPos.y);         //add the OS ui overlay
                UiMat = OverlayBlackMask(UiMat, OsMat); 
                OsMatLock.unlock();
            }
            DEBUG_LOG("drawn menu")
            UMat finished(cv::Size(1920, 1080), CV_8UC3,Scalar(0,0,0));
            vector<UMat> mats{UiMat,UiMat};
            
            cv::hconcat(mats,finished);
            DEBUG_LOG("concated mats")
            UiManager::managedUIs[0]->drawSurface = finished;  //write the final image to the psvr UI buffer
            UiManager::managedUIs[0]->draw();               //send the image to the psvr
    }

    void UiDrawer::drawStartupSequence(){
        cout << "opening external ressources" << endl;
        VideoCapture cap("./media/hud_startup.gif");
        cout << "opened video"<< endl;
        UMat overlay = imread("./media/hud_fixed.png",-1).getUMat(ACCESS_READ);
        cout << "read overlay" << endl;
        ui::UiDrawer::OverlayMat = overlay;
        if(!cap.isOpened()){
            cout << "failed to open hud start media" << endl;
            //return;
        }
        UMat frame;
        while(cap.read(frame))
        {
            frame = OverlayBlackMask(frame, overlay);
            imshow(ui::UiManager::managedUIs.at(0)->myWindow, frame);
            if(waitKey(30) >= 0) break;
        }
        cap.release();
    }

    void UiDrawer::drawMenu(){
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
        cv::rectangle(MenuMat, cv::Rect2i(0,((20*ui::UiController::selectedIndex)+20)+5,wd, 20), Scalar(200,0,0), 3, 8, 0);
        OsMatLock.lock();
        OsMat = MenuMat;
        OsMatLock.unlock();
    }

    void UiDrawer::runDrawUi(){
        cout << "starting ui drawer thread" << endl;
        ui::UiController::exitCalled = false;
        while(!ui::UiController::exitCalled){
            ui::UiDrawer::drawUi();
        }
    }

    UMat UiDrawer::prepareUiMat(){
        UMat blk960x1080(cv::Size(960, 1080), CV_8UC3,Scalar(0,0,0));
        return blk960x1080;
    }

    UMat UiDrawer::resizeIn(UMat input){
        UMat output;
        resize(input, output, Size(960, 1080), InterpolationFlags::INTER_NEAREST);
        return output;
    }
    ///if a non transparent picture is supplied (3 channels), it will be made transparent by using black as a mask
    UMat UiDrawer::OverlayBlackMask(UMat input, UMat toOverlay, int x, int y){
        //return input;
        if(input.cols < toOverlay.cols || input.rows < toOverlay.rows){
            cerr << "Wrong size for inout file!!! overlay was bigger" << endl;
        return input;
        }

        UMat toOverlayGRAY, mask;
        vector<UMat> Bands;

        if(toOverlay.channels() == 3){           //non transparent image, use black as mask
            cvtColor(toOverlay,toOverlayGRAY, COLOR_BGR2GRAY);          //picture to greyscale
            threshold(toOverlayGRAY, mask, 0, 255, THRESH_BINARY);      //greyscale to alpha (black or not)
        } else if (toOverlay.channels() == 4){   //transparent, use alpha layer as mask
            split(toOverlay,Bands);                                   // seperate channels
            vector<UMat> channels{ Bands[0],Bands[1],Bands[2] };
            merge(channels,toOverlay);                                       // glue together again
            mask = Bands[3];                                         // png's alpha channel used as mask
        }
        toOverlay.copyTo(input(cv::Rect(x,y,toOverlay.cols, toOverlay.rows)),mask);
        return input;
    }

    UMat UiDrawer::OverlayHISHMask(UMat input, UMat toOverlay){
        if(input.cols < toOverlay.cols || input.rows < toOverlay.rows) return input;

        UMat toOverlayGRAY, mask;
        vector<UMat> Bands;

        if(toOverlay.channels() == 3){           //non transparent image, use black as mask
            cvtColor(toOverlay,toOverlayGRAY, COLOR_BGR2GRAY);          //picture to greyscale
            threshold(toOverlayGRAY, mask, 0, 255, THRESH_BINARY);      //greyscale to alpha (black or not)
        } else if (toOverlay.channels() == 4){   //transparent, use alpha layer as mask
            split(toOverlay,Bands);                                   // seperate channels
            vector<UMat> channels{ Bands[0],Bands[1],Bands[2] };
            merge(channels,toOverlay);                                       // glue together again
            mask = Bands[3];                                         // png's alpha channel used as mask
        }
        toOverlay.copyTo(input(cv::Rect(0,0,toOverlay.cols, toOverlay.rows)),mask);
        return input;
    }
}
