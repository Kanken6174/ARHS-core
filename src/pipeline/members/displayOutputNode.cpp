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
        _managed->glInit();
        DEBUG_LOG("DisplayOutputNode on thread " << localThread->get_id() << " is done creating its opengl UI");
#endif
        inited = true;
    }
    _managed->drawAccess.lock();
    _managed->drawSurface = previous->getOutput();
    _managed->drawAccess.unlock();
    _managed->draw();
    outputLock.lock();
    output = _managed->drawSurface;
    outputLock.unlock();
}

std::string DisplayOutputNode::getName(){
    return "display output";
}