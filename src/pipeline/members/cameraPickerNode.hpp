#include "../abstract/pipelineNode.hpp"
#include "../../../model/hardware/cameras/_cam.hpp"

/// @brief this node will pick the right camera UMat from the ones available in its _sourceManager
class cameraPickerNode : public PipelineNode{
    public:
    cameraPickerNode(cameraManager* sourceManager);
    protected:
    virtual void processFrame() override;
    cameraManager* _sourceManager;
};