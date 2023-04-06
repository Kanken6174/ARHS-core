#include "pluginNode.hpp"
#include <opencv2/imgproc.hpp>
#include <map>
#include <iostream>

PluginNode::PluginNode(PipelineNode* _previous)
{
    isFirst = false;
    previous = _previous;
    fpsLimit = 60;
}

void PluginNode::processFrame()
{
    DEBUG_LOG("PluginNode on thread " << localThread->get_id() << " is processing its camera frame");
    try
    {
        if(!previous->getOutput().empty()){
        cv::UMat toProcess = previous->getOutput();
        DEBUG_LOG("PluginNode on thread " << localThread->get_id() << " fetched camera frame");
        Point2d p(0,0);
        for (SubNode* sn : subNodes)
            if(sn->enabled) sn->doWork(toProcess,p);
        DEBUG_LOG("PluginNode on thread " << localThread->get_id() << " processed camera frame");
        outputLock.lock();
        output = toProcess; // write the final image to the psvr UI buffer
        outputLock.unlock();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "\033[1;31m caught PluginNode::processFrame thread exception :"<< e.what() <<" \033[0m" << std::endl;
        exit(1);
    }
}

std::string PluginNode::getName(){
    return "PluginNode";
}