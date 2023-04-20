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
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <GL/glew.h>
#include <opencv2/core/opengl.hpp>

#include "menu.hpp"

using namespace std;
using namespace cv;
using namespace cv::ogl;
using namespace psvr;

/// @brief this class is used to process view logic and interaction [model]
class UiController : public MapObserver
{
public:
    std::map<std::string, Menu*> menus;
    void Update(const std::string &key, const std::string &value) override;
    UiController(psvr::Psvr *hmd);
    void update();
    std::vector<std::string> menuItemNames;
    bool showMenu;
    bool exitCalled;
    bool runIntro;
    string menuTitle;
    cv::Size2i menuSize;
    cv::Point2i menuPos;
    char *menutime;
    unsigned int selectedIndex;
    void activeMenuChange(std::string activeMenu){_activeMenu = activeMenu;}
    Menu* getActiveMenu(){return menus[_activeMenu];}
    Menu* getSpecificMenu(std::string name){return menus[name];}
private:
    std::string _activeMenu = "";
    psvr::Psvr *_hmd;

    void buildMenu();
};

class NavigateCommand : public Command{
    private:
    UiController* _backController;
    std::string _destination;
    public:
    NavigateCommand(std::string menuName, UiController* backController) : _destination(menuName), _backController(backController){}
    void Execute() const override { _backController->activeMenuChange(_destination);}
};

class ExitAppCommand : public Command{
    public:
    void Execute() const override { exit(0);}
};