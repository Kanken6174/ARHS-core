#include "../abstract/pipelineNode.hpp"

class UiDrawerNode : public PipelineNode{
    public:
    UiDrawerNode(UiController* backController);
    std::string getName() override;
    protected:
    void processFrame() override;
    UiController* _backController;
};