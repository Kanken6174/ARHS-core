#include "UiSupport.hpp"

cv::UMat UiSupport::makeMatStereo(cv::UMat toStereo)
{
    cv::UMat toreturn;
    std::vector<cv::UMat> mats{toStereo, toStereo};
    cv::hconcat(mats, toreturn);
    return toreturn;
}

cv::UMat UiSupport::prepareUiMat()
{
    return cv::UMat(cv::Size(960, 1080), CV_8UC3, cv::Scalar(0, 0, 0));
}

cv::UMat UiSupport::resizeIn(cv::UMat input)
{
    cv::UMat output;
    cv::resize(input, output, cv::Size(960, 1080), cv::InterpolationFlags::INTER_NEAREST);
    return output;
}

/// if a non transparent picture is supplied (3 channels), it will be made transparent by using black as a mask
cv::UMat UiSupport::OverlayBlackMask(cv::UMat input, cv::UMat toOverlay, int x, int y)
{
    // return input;
    if (input.cols < toOverlay.cols || input.rows < toOverlay.rows)
    {
        std::cerr << "Wrong size for input file!!! overlay was bigger" << std::endl;
        return input;
    }

    cv::UMat toOverlayGRAY, mask;
    std::vector<cv::UMat> Bands;

    if (toOverlay.channels() == 3)
    {                                                              // non transparent image, use black as mask
        cvtColor(toOverlay, toOverlayGRAY, cv::COLOR_BGR2GRAY);    // picture to greyscale
        threshold(toOverlayGRAY, mask, 0, 255, cv::THRESH_BINARY); // greyscale to alpha (black or not)
    }
    else if (toOverlay.channels() == 4)
    {                            // transparent, use alpha layer as mask
        split(toOverlay, Bands); // seperate channels
        std::vector<cv::UMat> channels{Bands[0], Bands[1], Bands[2]};
        merge(channels, toOverlay); // glue together again
        mask = Bands[3];            // png's alpha channel used as mask
    }
    toOverlay.copyTo(input(cv::Rect(x, y, toOverlay.cols, toOverlay.rows)), mask);
    return input;
}