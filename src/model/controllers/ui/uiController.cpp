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
    buildMenu();
    cout << "done init ui controller" << endl;
}

void UiController::Update(const std::string &key,const std::string &value)
{
    char c = value[0];
    switch (c)
    {
    case 'U':
        cout << c << "++" << endl;
        menus[_activeMenu]->selectedUp();
        break;
    case 'D':
        cout << c << "--" << endl;
        menus[_activeMenu]->selectedDown();
        break;
    case '1':   //1
        cout << c << "1" << endl;
        menus[_activeMenu]->clickback();
        break;
    case '2':   //<
        cout << c << "2" << endl;
        menus[_activeMenu]->clickb1();
        break;
    case '3':   //>
        cout << c << "3" << endl;
        menus[_activeMenu]->clickb2();
        break;
    case '0':   //2
        cout << c << "0" << endl;
        menus[_activeMenu]->clickok();
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

void UiController::buildMenu(){
    menus.clear();
    _activeMenu = "main menu";

    Command* navigateToMain = new NavigateCommand(_activeMenu,this);
    Menu* main = new Menu(_activeMenu,main,navigateToMain);     //it's the root so it navigates back to itself
    menus[main->getName()] = main;

    Menu* psvrMenu = new Menu("PSVR options",main, navigateToMain);
    menus[psvrMenu->getName()] = psvrMenu;

    Command* navigateToPsvr = new NavigateCommand(psvrMenu->getName(),this);

    menuitem* psvrOptions = new menuitem(navigateToPsvr);
    psvrOptions->setData("open psvr options");

    Command* startup = new StartupCommand(_hmd);
    Command* shutdown = new ShutdownCommand(_hmd);
    Command* vrmode = new VrModeCommand(_hmd);
    Command* cinemamode = new CinemaModeCommand(_hmd);

    ButtonItem* startBtn = new ButtonItem(startup);
    ButtonItem* stopBtn = new ButtonItem(shutdown);
    ButtonItem* vrBtn = new ButtonItem(vrmode);
    ButtonItem* cinemaBtn = new ButtonItem(cinemamode);

    startBtn->setData("startup psvr");
    stopBtn->setData("shutdown psvr");
    vrBtn->setData("set psvr VR mode");
    cinemaBtn->setData("set psvr Cinema mode");

    psvrMenu->addItem(startBtn);
    psvrMenu->addItem(stopBtn);
    psvrMenu->addItem(vrBtn);
    psvrMenu->addItem(cinemaBtn);
}