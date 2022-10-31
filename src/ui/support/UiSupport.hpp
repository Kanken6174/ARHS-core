#include <opencv2/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/opengl.hpp>
#include <iostream>

class UiSupport
{
public:
    static cv::UMat makeMatStereo(cv::UMat toStereo);
    static cv::UMat prepareUiMat();
    static cv::UMat resizeIn(cv::UMat input);
    static cv::UMat OverlayBlackMask(cv::UMat input, cv::UMat toOverlay, int x = 0, int y = 0);
};