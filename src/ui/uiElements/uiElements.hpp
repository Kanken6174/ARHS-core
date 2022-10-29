#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <vector>

using namespace cv;

//base UI element class (abstract)
struct UiElement{
    unsigned int xPosPixels;
    unsigned int yPosPixels;
    void drawSelf(UMat &input);
};
//sized ui element  (abstract)
struct SizedUiElement : UiElement{
    unsigned int widthPixels;
    unsigned int heightPixels;
    void drawSelf(UMat &input);
};

struct UiRect : SizedUiElement{
    unsigned int borderColor;
    unsigned int fillingColor;
    void drawSelf(UMat &input);
};

struct UiText : UiElement{
    std::string text;
    unsigned int fontSize;
    cv::Scalar textColor;
    cv::HersheyFonts font = HersheyFonts::FONT_HERSHEY_SIMPLEX;
    unsigned int thickness;
    unsigned int lineType = 0;
    bool leftOrigin = false;
    void drawSelf(cv::UMat &input){
    putText(input, UiText::text, Point(xPosPixels,yPosPixels), cv::FONT_HERSHEY_DUPLEX, fontSize, textColor, thickness, lineType, leftOrigin);
    }
};
//menu item container
struct UiMenuItem{
    std::vector<UiElement> elements;
};