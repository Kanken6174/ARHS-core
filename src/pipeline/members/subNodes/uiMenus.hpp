#include <string>
#include "../../abstract/pipelineNode.hpp"

class uiMenuItem : public MapObserver, public SubNode
{
public:
    uiMenuItem();
    void Update(const std::string &key, const std::string &value) override;
    void processFrame(cv::UMat &input, cv::Point2d &cursorPos) override;
    void addSubitem(uiMenuItem *item);

protected:
    std::map<std::string, std::string> internalData;
    vector<uiMenuItem *> subitems;
};

class uiNumberPickerItem : public uiMenuItem
{
public:
    void processFrame(cv::UMat &input, cv::Point2d &cursorPos) override
    {
        cv::putText(input, cv::format("< %s >", internalData["data"]), cv::Point2i(5, cursorPos.y += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1, 8, false);
    }
};

class uiCheckerItem : public uiMenuItem
{
public:
    uiCheckerItem()
    {
        internalData["enabled"] = "false";
    }

    void processFrame(cv::UMat &input, cv::Point2d &cursorPos) override
    {
        cv::circle(input, cursorPos, 5, (0, 0, 255), internalData["enabled"] == "true" ? -1 : 1);
        cv::putText(input, cv::format("%s", internalData["name"]), cv::Point2i(5, cursorPos.y += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1, 8, false);
    }
};