#include "cameraPickerNode.hpp"

cameraPickerNode::cameraPickerNode(cameraManager* sourceManager) : _sourceManager(sourceManager)
{
    cost = 0.25;
}

void cameraPickerNode::processFrame(){
    outputLock.lock();
    _sourceManager->accessLocks[0]->lock();
    output = _sourceManager->captures[0];
    _sourceManager->accessLocks[0]->unlock();
    outputLock.unlock();
}