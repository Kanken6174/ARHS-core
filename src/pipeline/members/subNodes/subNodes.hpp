#include "../../abstract/pipelineNode.hpp"
#include "../zbarAnalysisNode.hpp"
#include <map>

class FpsCounter : public SubNode
{
public:
    void processFrame(cv::UMat &input, cv::Point2d &cursorPos) override;
    void addChecker(std::string name, framerateChecker *fc);

protected:
    std::map<std::string, framerateChecker *> checkers;
};

class StaticImageOverlayer : public SubNode
{
public:
    void processFrame(cv::UMat &input, cv::Point2d &cursorPos) override;
    void setImage(std::string str);
protected:
    cv::UMat image;
};

class ZbarOverlayer : public SubNode
{
public:
    ZbarOverlayer(zbarScanner* backend);
    void processFrame(cv::UMat &input, cv::Point2d &cursorPos) override;
protected:
    zbarScanner* localScanner;
};