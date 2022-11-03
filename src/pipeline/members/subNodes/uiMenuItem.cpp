#include "uiMenus.hpp"
#include <opencv2/imgproc.hpp>
template <>
void uiMenuItem<std::string>::processFrame(cv::UMat& input, cv::Point2d& cursorPos){
        cv::putText(input, underlyingData, cv::Point2i(5, cursorPos.y += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1, 8, false);
}