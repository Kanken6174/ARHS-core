#include "zbarAnalysisNode.hpp"
#include <opencv2/imgproc.hpp>
#include <map>
#include <iostream>

ZbarAnalysisNode::ZbarAnalysisNode(PipelineNode* _previous, zbarScanner* scanner) : localScanner(scanner)
{
    isFirst = false;
    previous = _previous;
    fpsLimit = 60;
}

void ZbarAnalysisNode::processFrame()
{
    DEBUG_LOG("ZbarAnalysisNode on thread " << localThread->get_id() << " is processing its camera frame");
    try
    {
        if(!previous->getOutput().empty()){
        cv::UMat toDecode = previous->getOutput();
        DEBUG_LOG("ZbarAnalysisNode on thread " << localThread->get_id() << " fetched camera frame");
        localScanner->decode(toDecode);
        DEBUG_LOG("ZbarAnalysisNode on thread " << localThread->get_id() << " processed camera frame");
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "\033[1;31m caught ZbarAnalysisNode::processFrame thread exception :"<< e.what() <<" \033[0m" << std::endl;
        exit(1);
    }
}

std::string ZbarAnalysisNode::getName(){
    return "zbar analyzer";
}