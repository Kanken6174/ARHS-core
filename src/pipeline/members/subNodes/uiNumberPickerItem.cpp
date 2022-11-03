#include "uiMenus.hpp"
#include <opencv2/imgproc.hpp>

template <>
void uiMenuItem<float>::processFrame(cv::UMat& input, cv::Point2d& cursorPos){
        cv::putText(input, cv::format("< %f >",underlyingData), cv::Point2i(5, cursorPos.y += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1, 8, false);
}
template <>
void uiMenuItem<double>::processFrame(cv::UMat& input, cv::Point2d& cursorPos){
        cv::putText(input, cv::format("< %f >",underlyingData), cv::Point2i(5, cursorPos.y += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1, 8, false);
}
template <>
void uiMenuItem<int>::processFrame(cv::UMat& input, cv::Point2d& cursorPos){
        cv::putText(input, cv::format("< %i >",underlyingData), cv::Point2i(5, cursorPos.y += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1, 8, false);
}
template <>
void uiMenuItem<char>::processFrame(cv::UMat& input, cv::Point2d& cursorPos){
        cv::putText(input, cv::format("< %c >",underlyingData), cv::Point2i(5, cursorPos.y += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1, 8, false);
}