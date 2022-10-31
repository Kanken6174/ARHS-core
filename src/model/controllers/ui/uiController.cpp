#include "uiController.hpp"

UiController::UiController()
{
    std::cout << "init ui controller" << endl;
    showMenu = true;
    menuSize = cv::Size2i(400, 400);
    menuPos = cv::Point2i(DEFAULT_UI_SIZE_X - menuSize.width, (DEFAULT_UI_SIZE_Y / 2) - (menuSize.height / 2)); // centered right
    selectedIndex = 0;
    menuItemNames = {"set vr mode", "set cinema mode", "settings"};
    vector<std::function<void()>> functions = {psvr::Psvr::vrmode, psvr::Psvr::cinemaMode, UiController::openSettings};
    unsigned int i = 0;
    for (std::string name : menuItemNames)
    {
        menuItems[name] = functions.at(i);
        i++;
    }
    update();
    cout << "done init ui controller" << endl;
}

void UiController::update()
{
    time_t now = time(0);
    menutime = ctime(&now);
    menuTitle = std::string("P-OS ") + VERSION + " " + menutime;
}

void UiController::selectedUp()
{
    if (selectedIndex < menuItems.size() - 1)
        selectedIndex++;
}

void UiController::selectedDown()
{
    if (selectedIndex > 0)
        selectedIndex--;
}

void UiController::openSettings()
{
}

void UiController::click()
{
    exitCalled = true;
    // std::invoke(menuItems[menuItemNames.at(selectedIndex)]);
}