#include "displayOutputNode.hpp"

DisplayOutputNode::DisplayOutputNode(PipelineNode* predecessor, Window *managed) : _managed(managed)
{
    previous = predecessor;
    output = NULL;
    cost = 2;
}

void DisplayOutputNode::processFrame()
{
    if (!inited)
    {
#ifdef OGLWIN
        namedWindow(_managed->myWindow, WINDOW_OPENGL);
        setWindowProperty(_managed->myWindow, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
        cv::setOpenGlContext(_managed->myWindow);
        moveWindow(_managed->myWindow, DEFAULT_UI_OFFSET_X + 960, DEFAULT_UI_OFFSET_Y);
#endif
        inited = true;
    }
    _managed->drawAccess.lock();
    _managed->drawSurface = previous->getOutput();
    _managed->drawAccess.unlock();
    _managed->draw();
}