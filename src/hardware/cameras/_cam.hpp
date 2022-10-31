#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <regex>
#include <execution>
#include <vector>
#include <thread>
#include <mutex> 
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio_c.h>
#include "../../threadweaver/threadweaver.hpp"

using namespace std;
using namespace cv;

std::vector<std::string> listCameras();

class camera{
    public:
    uint path;
    VideoCapture* source;
    int Yindex = 0; //index for the stitcher
};

class cameraManager{
    public:
    static std::vector<camera*> videoSources;
    static std::vector<UMat> captures;
    static std::vector<std::mutex*> accessLocks;
    static bool runCaptureThread;
    static int init();
    static void runCapture();
    static void stopCapture();
    static void runCaptureForCamera(camera* c, uint index);
};