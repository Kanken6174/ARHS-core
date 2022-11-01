#pragma once
#include "../abstract/pipelineNode.hpp"
#include "./../../model/hardware/cameras/_cam.hpp"

/// @brief this node will pick the right camera UMat from the ones available in its _sourceManager
class cameraPickerNode : public PipelineNode{
    public:
    std::string getName() override;
    cameraPickerNode(cameraManager* sourceManager);
    protected:
    void processFrame() override;
    cameraManager* _sourceManager;
};