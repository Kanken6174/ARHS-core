/*#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include <functional>

#include <GL/glut.h>
*/
#pragma once
#include "../../hardware/cameras/_cam.hpp"
#include "../../hardware/psvr/_psvr.hpp"
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/opengl.hpp>

#include "../../patterns/observer/observable.hpp"

#define DEFAULT_UI_WINDOW_AMOUNT 1 // 2 windows, one for each eye
#define DEFAULT_UI_OFFSET_X 1080   // 1080
#define DEFAULT_UI_OFFSET_Y 0
#define DEFAULT_UI_SIZE_X 1920 // psvr is 960x1080 per eye
#define DEFAULT_UI_SIZE_Y 1080

using namespace std;
using namespace cv;
using namespace cv::ogl;
using namespace psvr;

/// @brief this class is used to process view logic and interaction [model]
class UiController : public Observer
{
public:
    void Update(const std::string &message_from_subject) override;
    UiController(psvr::Psvr* hmd);
    void selectedUp();
    void selectedDown();
    void click();
    void update();
    void openSettings();
    void cinemaMode();
    void vrMode();
    std::vector<std::string> menuItemNames;
    bool showMenu;
    bool exitCalled;
    bool runIntro;
    string menuTitle;
    cv::Size2i menuSize;
    cv::Point2i menuPos;
    unsigned int selectedIndex;
    map<std::string, std::function<void()>> menuItems;
    char *menutime;
    private:
    psvr::Psvr* _hmd;
};
