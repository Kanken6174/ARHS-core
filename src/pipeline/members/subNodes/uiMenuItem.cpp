#include "uiMenus.hpp"
#include <opencv2/imgproc.hpp>

void uiMenuItem::addSubitem(uiMenuItem *item)
{
        subitems.push_back(item);
}

void uiMenuItem::Update(const std::string &key, const std::string &value)
{
        internalData[key] = value;
}

void uiMenuItem::processFrame(cv::UMat &input, cv::Point2d &cursorPos)
{
        if (enabled)
                cv::putText(input, internalData["data"].c_str(), cv::Point2i(5, cursorPos.y += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1, 8, false);
}