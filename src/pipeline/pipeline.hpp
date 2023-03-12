#include "./abstract/pipelineNode.hpp"
#include "./members/cameraPickerNode.hpp"
#include "./members/displayOutputNode.hpp"
#include "./members/uiDrawerNode.hpp"
#include "./members/uiMergerNode.hpp"
#include "./members/videoCaptureNode.hpp"
#include "./members/pluginNode.hpp"

#define PIPELINE_UI_DRAWER_NODE 3

class Pipeline{
    private:
    std::vector<PipelineNode*> nodes;
    void startPipeline();
    public:
    Pipeline();
    std::vector<PipelineNode*> getNodes(){return nodes;}
};