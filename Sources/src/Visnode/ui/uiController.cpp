#include "_ui.hpp"

bool ui::UiController::showMenu;
bool ui::UiController::exitCalled;
cv::Size2i ui::UiController::menuSize;
cv::Point2i ui::UiController::menuPos;
unsigned int ui::UiController::selectedIndex;
map<std::string, std::function<void()>> ui::UiController::menuItems;
string ui::UiController::menuTitle;
char* ui::UiController::menutime;
vector<std::string> ui::UiController::menuItemNames = {"set vr mode","set cinema mode","settings"};

void ui::UiController::init(){
    std::cout << "init ui controller" << endl;
    showMenu = true;
    menuSize = cv::Size2i(400,400);
    menuPos = cv::Point2i(DEFAULT_UI_SIZE_X-menuSize.width,(DEFAULT_UI_SIZE_Y/2)-(menuSize.height/2));    //centered right
    selectedIndex = 0;
    menuItemNames = {"set vr mode","set cinema mode","settings"};
    vector<std::function<void()>> functions = {psvr::Psvr::vrmode, psvr::Psvr::cinemaMode, UiController::openSettings};
    unsigned int i = 0;
    for(std::string name : menuItemNames){
        menuItems[name] = functions.at(i);
        i++;
    }
    update();
    cout << "done init ui controller" << endl;
}

void ui::UiController::update(){
    time_t now = time(0);
    menutime = ctime(&now);
    menuTitle = std::string("P-OS V0.1 ") + menutime;
}

void ui::UiController::selectedUp(){
    if(selectedIndex < menuItems.size()-1) selectedIndex++;
}

void ui::UiController::selectedDown(){
    if(selectedIndex > 0) selectedIndex--;
}

void ui::UiController::openSettings(){

}

void ui::UiController::click(){
    ui::UiController::exitCalled = true;
    //std::invoke(menuItems[menuItemNames.at(selectedIndex)]);
}
