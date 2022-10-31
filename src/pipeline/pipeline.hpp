#include "./abstract/pipelineNode.hpp"
#include "./members/cameraPickerNode.hpp"
#include "./members/displayOutputNode.hpp"
#include "./members/uiDrawerNode.hpp"
#include "./members/uiMergerNode.hpp"

class Pipeline{
    private:
    std::vector<PipelineNode*> nodes;
    public:
    Pipeline();
};