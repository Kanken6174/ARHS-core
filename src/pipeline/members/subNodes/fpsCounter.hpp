#include "../../abstract/pipelineNode.hpp"
#include <map>

class FpsCounter : public SubNode
{
public:
    void processFrame(cv::UMat &input, cv::Point2d &cursorPos) override;
    void addChecker(std::string name, framerateChecker *fc);

protected:
    std::map<std::string, framerateChecker *> checkers;
};