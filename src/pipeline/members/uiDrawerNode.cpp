#include "uiDrawerNode.hpp"
#include <opencv2/imgproc.hpp>
#include <map>
#include <iostream>

UiDrawerNode::UiDrawerNode(UiController* backController) : _backController(backController)
{
    isFirst = true;
    previous = nullptr;
}

void UiDrawerNode::processFrame()
{
    DEBUG_LOG("UiDrawerNode on thread " << localThread->get_id() << " is procesing its camera frame");
    try
    {
        if(_backController == nullptr){
            DEBUG_LOG("UiDrawerNode on thread " << localThread->get_id() << " had no back controller, exitting...");
        }

        int &wd = _backController->menuSize.width;
        int &he = _backController->menuSize.height;
        unsigned int stackerIndex = 0;
        cv::UMat MenuMat = cv::UMat(cv::Size(960, 1080), CV_8UC3, cv::Scalar(0, 0, 0));
        cv::rectangle(MenuMat, cv::Rect2i(0, 0, wd, he), cv::Scalar(255, 0, 0), 5, 8, 0);
        _backController->update();
        cv::putText(MenuMat, _backController->menuTitle, cv::Point2i(5, stackerIndex += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255), 1, 8, false);
        for (String str : _backController->menuItemNames)
        {
            cv::putText(MenuMat, str, cv::Point2i(5, stackerIndex += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255), 1, 8, false);
        }
        Point2d pc = Point2d(0,stackerIndex);
        for (SubNode* sn : subNodes)
            if(sn->enabled) sn->processFrame(MenuMat,pc);
        stackerIndex = pc.y;
        cv::rectangle(MenuMat, cv::Rect2i(0, ((20 * _backController->selectedIndex) + 20) + 5, wd, 20), Scalar(200, 0, 0), 3, 8, 0);
        outputLock.lock();
        output = MenuMat;
        outputLock.unlock();
    }
    catch (...)
    {
        std::cerr << "\033[1;31m caught DrawUi::drawMenu thread exception \033[0m" << std::endl;
        exit(1);
    }
}

std::string UiDrawerNode::getName(){
    return "ui drawer";
}