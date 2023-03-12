#include "../abstract/pipelineNode.hpp"
/// @brief this class is used to run plugins
class PluginNode : public PipelineNode
{
public:
    PluginNode(PipelineNode* _previous);
    std::string getName() override;
protected:
    void processFrame() override;
};