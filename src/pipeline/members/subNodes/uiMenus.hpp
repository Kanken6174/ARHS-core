#include <string>
#include "../../abstract/pipelineNode.hpp"

template<typename T> class uiMenuItem : public Observable, public SubNode
{
    public:
    void processFrame(cv::UMat &input, cv::Point2d &cursorPos) override;
    protected:
    std::vector<uiMenuItem> items;
    T underlyingData;
};

template<typename T> class uiNumberPickerItem : public uiMenuItem<T>
{
    public:
    void processFrame(cv::UMat &input, cv::Point2d &cursorPos) override;
};