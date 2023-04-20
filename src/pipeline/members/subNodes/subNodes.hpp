#include "../../abstract/pipelineNode.hpp"
#include "../zbarAnalysisNode.hpp"
#include "../../../graphics/Camera.h"
#include "../../../graphics/FlyingWindow.h"
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

class OpenglTestRenderer : public SubNode
{
public:
    OpenglTestRenderer();
    void processFrame(cv::UMat &input, cv::Point2d &cursorPos) override;
protected:
    FlyingWindow* subject;
    void setup();
    Camera camera;
    Model model1;
    Model model2;
};