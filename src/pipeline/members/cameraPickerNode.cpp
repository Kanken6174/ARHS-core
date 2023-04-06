#include "cameraPickerNode.hpp"

cameraPickerNode::cameraPickerNode(cameraManager* sourceManager) : _sourceManager(sourceManager)
{
    isFirst = true;
    cost = 0.25;
}

void cameraPickerNode::processFrame(){
    DEBUG_LOG("cameraPickerNode on thread " << localThread->get_id() << " is picking its camera frame");
    if(_sourceManager == nullptr || _sourceManager->accessLocks.empty() || _sourceManager->captures.empty()){
        DEBUG_LOG("cameraPickerNode on thread " << localThread->get_id() << " had no source manager or captures, exitting...");
        exit(1);
    }
    outputLock.lock();
    _sourceManager->accessLocks[0]->lock();
    output = _sourceManager->captures[0];
    _sourceManager->accessLocks[0]->unlock();
    Point2d p(0,0);
    for (SubNode* sn : subNodes)
        if(sn->enabled) sn->doWork(output,p);
    outputLock.unlock();
    
    DEBUG_LOG("cameraPickerNode on thread " << localThread->get_id() << " is done picking its camera frame");
}

std::string cameraPickerNode::getName(){
    return "camera Picker";
}