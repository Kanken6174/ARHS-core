#include "subNodes.hpp"
#include <opencv2/imgproc.hpp>

void FpsCounter::processFrame(cv::UMat& input, cv::Point2d& cursorPos){
    for(std::pair<std::string, framerateChecker*> sfc : checkers){
        int fps = sfc.second->fps;
        cv::putText(input, cv::format("Eps %s: %d", sfc.first.c_str(),fps), cv::Point2i(5, cursorPos.y += 20), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1, 8, false);
    }
}

void FpsCounter::addChecker(std::string name, framerateChecker* fc){
    checkers.emplace(name, fc);
}