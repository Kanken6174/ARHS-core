#include "_ui.hpp"
Mat ui::UiDrawer::OverlayMat;
Mat ui::UiDrawer::OsMat;   //drawn on certain events
std::mutex ui::UiDrawer::OsMatLock;

            //UiMat = prepareUiMat();
            //surface.copyTo(UiMat(cv::Rect((UiMat.cols/2)-(surface.cols/2),(UiMat.rows/2)-(surface.rows/2),surface.cols, surface.rows)));
            //UiMat = OverlayBlackMask(UiMat, overlay);

namespace ui{
    //draws the UI for the left screen of the psvr
    void UiDrawer::drawUiL(){
            Mat UiMat = prepareUiMat();                 //prepare black background
            cameraManager::accessLocks[0]->lock();      //lock the capture access
            Mat surface = cameraManager::captures[0];   //retreive latest camera frame
            cameraManager::accessLocks[0]->unlock();    //unlock capture access
            if(surface.rows <= 0 || surface.cols <= 0) return;  //check for empty frame
            surface = resizeIn(surface);                //resize the frame to the standard format
            //Copy the frame in the center of the background
            surface.copyTo(UiMat(cv::Rect((UiMat.cols/2)-(surface.cols/2),(UiMat.rows/2)-(surface.rows/2),surface.cols, surface.rows)));
            UiMat = OverlayBlackMask(UiMat, OverlayMat);    //add the fixed overlay
            if(UiController::showMenu){
                UiDrawer::drawMenu();
                OsMatLock.lock();
                UiMat = OverlayBlackMask(UiMat, OsMat, ui::UiController::menuPos.x,ui::UiController::menuPos.y);         //add the OS ui overlay
                OsMatLock.unlock();
            }
            UiManager::managedUIs[0]->drawSurface = UiMat;  //write the final image to the psvr UI buffer
            UiManager::managedUIs[0]->draw();               //send the image to the psvr
    }

    void UiDrawer::drawUiR(){
            Mat UiMat = prepareUiMat();
            cameraManager::accessLocks[0]->lock();
            Mat surface = cameraManager::captures[0];
            cameraManager::accessLocks[0]->unlock();
            if(surface.rows <= 0 || surface.cols <= 0) return;
            surface = resizeIn(surface);
            surface.copyTo(UiMat(cv::Rect((UiMat.cols/2)-(surface.cols/2),(UiMat.rows/2)-(surface.rows/2),surface.cols, surface.rows)));
            UiMat = OverlayBlackMask(UiMat, OverlayMat);
            if(UiController::showMenu){
                UiDrawer::drawMenu();
                OsMatLock.lock();
                UiMat = OverlayBlackMask(UiMat, OsMat, ui::UiController::menuPos.x,ui::UiController::menuPos.y);         //add the OS ui overlay
                OsMatLock.unlock();
            }
            UiManager::managedUIs[1]->drawSurface = UiMat;
            UiManager::managedUIs[1]->draw();
    }

    void UiDrawer::drawStartupSequence(){
        VideoCapture cap("./media/hud_startup.gif");
        Mat overlay = imread("./media/hud_fixed.png",-1);
        cout << "read overlay" << endl;
        ui::UiDrawer::OverlayMat = overlay;
        if(!cap.isOpened()){
            cout << "failed to open hud start media" << endl;
            //return;
        }
        Mat frame;
        for(;;)
        {
            if(!cap.read(frame)) break;
            frame = OverlayBlackMask(frame, overlay);
            imshow(ui::UiManager::managedUIs.at(0)->myWindow, frame);
            imshow(ui::UiManager::managedUIs.at(1)->myWindow, frame);
            if(waitKey(30) >= 0) break;
        }
        cap.release();
    }

    void UiDrawer::drawMenu(){
        int& wd = UiController::menuSize.width;
        int& he = UiController::menuSize.height;
        unsigned int stackerIndex = 0;
        Mat MenuMat(cv::Size(wd, he), CV_8UC3,Scalar(0,0,0));
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

    Mat UiDrawer::prepareUiMat(){
        Mat blk960x1080(cv::Size(960, 1080), CV_8UC3,Scalar(0,0,0));
        return blk960x1080;
    }

    Mat UiDrawer::resizeIn(Mat input){
        Mat output;
        resize(input, output, Size(960, 1080), InterpolationFlags::INTER_LINEAR);
        return output;
    }

    ///if a non transparent picture is supplied (3 channels), it will be made transparent by using black as a mask
    Mat UiDrawer::OverlayBlackMask(Mat input, Mat toOverlay, int x, int y){
        if(input.cols < toOverlay.cols || input.rows < toOverlay.rows) return input;

        Mat toOverlayGRAY, mask;
        vector<Mat> Bands;

        if(toOverlay.channels() == 3){           //non transparent image, use black as mask
            cvtColor(toOverlay,toOverlayGRAY, COLOR_BGR2GRAY);          //picture to greyscale
            threshold(toOverlayGRAY, mask, 0, 255, THRESH_BINARY);      //greyscale to alpha (black or not)
        } else if (toOverlay.channels() == 4){   //transparent, use alpha layer as mask
            split(toOverlay,Bands);                                   // seperate channels
            Mat channels[3] = { Bands[0],Bands[1],Bands[2] };
            merge(channels,3,toOverlay);                                       // glue together again
            mask = Bands[3];                                         // png's alpha channel used as mask
        }
        toOverlay.copyTo(input(cv::Rect(x,y,toOverlay.cols, toOverlay.rows)),mask);
        return input;
    }

    Mat UiDrawer::OverlayHISHMask(Mat input, Mat toOverlay){
                if(input.cols < toOverlay.cols || input.rows < toOverlay.rows) return input;

        Mat toOverlayGRAY, mask;
        vector<Mat> Bands;

        if(toOverlay.channels() == 3){           //non transparent image, use black as mask
            cvtColor(toOverlay,toOverlayGRAY, COLOR_BGR2GRAY);          //picture to greyscale
            threshold(toOverlayGRAY, mask, 0, 255, THRESH_BINARY);      //greyscale to alpha (black or not)
        } else if (toOverlay.channels() == 4){   //transparent, use alpha layer as mask
            split(toOverlay,Bands);                                   // seperate channels
            Mat channels[3] = { Bands[0],Bands[1],Bands[2] };
            merge(channels,3,toOverlay);                                       // glue together again
            mask = Bands[3];                                         // png's alpha channel used as mask
        }
        toOverlay.copyTo(input(cv::Rect(0,0,toOverlay.cols, toOverlay.rows)),mask);
        return input;
    }
}
