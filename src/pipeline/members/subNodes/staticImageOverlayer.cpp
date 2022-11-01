#include "subNodes.hpp"
#include "./../../../ui/support/UiSupport.hpp"

void StaticImageOverlayer::processFrame(cv::UMat& input, cv::Point2d& cursorPos){
    input = UiSupport::OverlayBlackMask(input, image);
}

void StaticImageOverlayer::setImage(std::string str){
    image = cv::imread("./media/hud_fixed.png",-1).getUMat(cv::ACCESS_READ);
}