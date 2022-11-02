#include "displayOutputNode.hpp"

DisplayOutputNode::DisplayOutputNode(PipelineNode* predecessor, Window *managed) : _managed(managed)
{
    previous = predecessor;
    isLast = true;
    //output = NULL;
    cost = 2;
    inited = false;
}

void DisplayOutputNode::processFrame()
{
    DEBUG_LOG("DisplayOutputNode on thread " << localThread->get_id() << " is procesing its camera frame");
    if (!inited)
    {
#ifdef OGLWIN
        DEBUG_LOG("DisplayOutputNode on thread " << localThread->get_id() << " is creating its opengl UI");
        cv::namedWindow(_managed->myWindow, cv::WINDOW_OPENGL);
        setWindowProperty(_managed->myWindow, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
        cv::setOpenGlContext(_managed->myWindow);
        cv::moveWindow(_managed->myWindow, DEFAULT_UI_OFFSET_X + 960, DEFAULT_UI_OFFSET_Y);
        DEBUG_LOG("DisplayOutputNode on thread " << localThread->get_id() << " is done creating its opengl UI");
#endif
        inited = true;
    }
    _managed->drawAccess.lock();
    _managed->drawSurface = previous->getOutput();
    _managed->drawAccess.unlock();
    _managed->draw();
}

std::string DisplayOutputNode::getName(){
    return "display output";
}