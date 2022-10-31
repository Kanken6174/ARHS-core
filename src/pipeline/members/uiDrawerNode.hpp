#include "../abstract/pipelineNode.hpp"
#include "../../model/controllers/ui/uiController.hpp"

class UiDrawerNode : public PipelineNode{
    public:
    UiDrawerNode();
    protected:
    virtual void processFrame() override;
    UiController* _backController;
};