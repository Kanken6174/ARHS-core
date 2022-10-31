#include "../abstract/pipelineNode.hpp"
#include "../../model/controllers/ui/uiController.hpp"
/// @brief this class is used to merge the camera's frame and the UI mat
class UiMergerNode : public PipelineNode
{
public:
    UiMergerNode(PipelineNode* previous,PipelineNode* menuDrawer, UiController* backController);
protected:
    void processFrame() override;
    PipelineNode* _menuDrawer;
    UiController* _backController;
};