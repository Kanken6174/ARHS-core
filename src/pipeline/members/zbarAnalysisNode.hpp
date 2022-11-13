#include "../abstract/pipelineNode.hpp"
#include "../../processing/zbar/zbar.hpp"
/// @brief this class is used to check a mat for any bar codes
class ZbarAnalysisNode : public PipelineNode
{
public:
    ZbarAnalysisNode(PipelineNode* _previous,zbarScanner* scanner);
    std::string getName() override;
protected:
    void processFrame() override;
    zbarScanner* localScanner;
};