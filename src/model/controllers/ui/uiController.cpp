#include "uiController.hpp"

UiController::UiController(psvr::Psvr *hmd) : _hmd(hmd)
{
    std::cout << "init ui controller" << endl;
    showMenu = true;
    menuSize = cv::Size2i(400, 400);
    menuPos = cv::Point2i(DEFAULT_UI_SIZE_X - menuSize.width, (DEFAULT_UI_SIZE_Y / 2) - (menuSize.height / 2)); // centered right
    selectedIndex = 0;
    menuItemNames = {"set vr mode", "set cinema mode", "settings","quit"};
    unsigned int i = 0;
    update();
    cout << "done init ui controller" << endl;
}

void UiController::Update(const std::string &message_from_subject)
{
    char c = message_from_subject[0];
    switch (c)
    {
    case 'U':
        cout << c << "++" << endl;
        selectedUp();
        break;
    case 'D':
        cout << c << "--" << endl;
        selectedDown();
        break;
    case '1':
        cout << c << "1" << endl;
        click();
        break;
    case '2':
        cout << c << "2" << endl;
        click();
        break;
    case '3':
        cout << c << "3" << endl;
        click();
        break;
    case '0':
        cout << c << "0" << endl;
        click();
        break;
    default:
        cout << c << endl;
        break;
    }
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

void UiController::cinemaMode()
{
    _hmd->cinemaMode();
}

void UiController::vrMode()
{
    _hmd->vrmode();
}

void UiController::click()
{
    //exitCalled = true;
    // std::invoke(menuItems[menuItemNames.at(selectedIndex)]);
    switch (selectedIndex)
    {
    case 0:
    vrMode();
        break;
    case 1:
    cinemaMode();
        break;
    case 2:
    openSettings();
        break;
    case 3:
    exit(0);
        break;
    default:
        break;
    }
}