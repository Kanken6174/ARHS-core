#include "uiMergerNode.hpp"
#include "../../ui/support/UiSupport.hpp"

UiMergerNode::UiMergerNode(PipelineNode* _previous,PipelineNode* menuDrawer, UiController* backController) : _menuDrawer(menuDrawer), _backController(backController)
{
    isFirst = false;
    isLast = false;
    previous = _previous;
}

void UiMergerNode::processFrame()
{
    DEBUG_LOG("UiMergerNode on thread " << localThread->get_id() << " is procesing its camera frame");
    cv::UMat UiMat = UiSupport::prepareUiMat();         // prepare black background 960*1080
    cv::UMat cameraFrame = previous->getOutput();

    if (cameraFrame.rows <= 0 || cameraFrame.cols <= 0)
        return;                                     // check for empty frame

    Point2d p(0,0);
    for (SubNode* sn : subNodes)
        if(sn->enabled) sn->doWork(cameraFrame,p);

    cameraFrame = UiSupport::resizeIn(cameraFrame); // resize the frame to the standard format
    // Copy the frame in the center of the background
    cameraFrame.copyTo(UiMat(cv::Rect((UiMat.cols / 2) - (cameraFrame.cols / 2), (UiMat.rows / 2) - (cameraFrame.rows / 2), cameraFrame.cols, cameraFrame.rows)));
    if (_backController->showMenu)
    {
        // UiMat = OverlayBlackMask(UiMat, OsMat, ui::UiController::menuPos.x,ui::UiController::menuPos.y);         //add the OS ui overlay
        UiMat = UiSupport::OverlayBlackMask(UiMat, _menuDrawer->getOutput());
    }
    cv::UMat finished = UiSupport::makeMatStereo(UiMat);

    outputLock.lock();
    output = finished; // write the final image to the psvr UI buffer
    outputLock.unlock();
}

std::string UiMergerNode::getName(){
    return "ui merger";
}