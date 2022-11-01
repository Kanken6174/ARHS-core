#include "../abstract/pipelineNode.hpp"
#include "./../../model/windows/window.hpp"

/// @brief this node will pick the right camera UMat from the ones available in its _sourceManager
class DisplayOutputNode : public PipelineNode
{
public:
    DisplayOutputNode(PipelineNode* predecessor, Window* managed);
    std::string getName() override;
protected:
    void processFrame() override;
    bool inited = false;
    Window *_managed;
};