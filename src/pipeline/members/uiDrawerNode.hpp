#include "../abstract/pipelineNode.hpp"
#include "../../model/controllers/ui/uiController.hpp"

class UiDrawerNode : public PipelineNode{
    public:
    UiDrawerNode(UiController* backController);
    protected:
    void processFrame() override;
    UiController* _backController;
};