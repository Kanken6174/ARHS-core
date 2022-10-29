#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <vector>

using namespace cv;

class Widget{
    public:
    int x,y,width,height = 0;
    UMat output;
};