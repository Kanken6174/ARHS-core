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
        cv::rectangle(MenuMat, cv::Rect2i(0, 0, wd, 45), cv::Scalar(255, 0, 0), 3, 8, 0);
        _backController->update();
        Menu* activeMenu = _backController->getActiveMenu();
        cv::putText(MenuMat, _backController->menuTitle, cv::Point2i(5, stackerIndex += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255), 1, 8, false);
        cv::putText(MenuMat, cv::format("%s", activeMenu->getName().c_str()), cv::Point2i(5, stackerIndex += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1, 8, false);
        unsigned int i = 0;
        for(baseItem* b : activeMenu->getItems()){
            cv::Scalar color = activeMenu->getSelectedIndex() == i ? Scalar(0, 0, 200) : Scalar(255, 255, 255);
            switch (b->getTrueType())
            {
            case MenuitemT:
            cv::putText(MenuMat, cv::format("%s", static_cast<menuitem*>(b)->getData().c_str()), cv::Point2i(5, stackerIndex += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, color, 1, 8, false);
            break;
            case CheckerItemT:
            cv::circle(MenuMat, cv::Point2i(0, stackerIndex), 5, (0, 0, 255), static_cast<CheckerItem*>(b)->getData() ? -1 : 1);
            cv::putText(MenuMat, cv::format(" %s", static_cast<CheckerItem*>(b)->getName().c_str()), cv::Point2i(5, stackerIndex += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, color, 1, 8, false);
            break;
            case ExectuableT:
            cv::putText(MenuMat, cv::format("> %s", static_cast<ButtonItem*>(b)->getData().c_str()), cv::Point2i(5, stackerIndex += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, color, 1, 8, false);
            break;
            case NumberPickerItemT:
            cv::putText(MenuMat, cv::format("< %d > %s", static_cast<NumberPickerItem*>(b)->getData(), static_cast<NumberPickerItem*>(b)->getName().c_str()), cv::Point2i(5, stackerIndex += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, color, activeMenu->selecting && i == activeMenu->getSelectedIndex() ? 2 : 1, 8, false);
            break;

            default:
                break;
            }
            i++;
        }
        /*for (String str : _backController->menuItemNames)
        {
            cv::putText(MenuMat, str, cv::Point2i(5, stackerIndex += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255), 1, 8, false);
        }*/
        Point2d pc = Point2d(0,stackerIndex);
        cv::rectangle(MenuMat, cv::Rect2i(0, stackerIndex+5, wd, 1), Scalar(200, 0, 0), 3, 8, 0);
        for (SubNode* sn : subNodes)
            if(sn->enabled) sn->doWork(MenuMat,pc);
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