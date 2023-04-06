#include "uiController.hpp"

UiController::UiController(psvr::Psvr *hmd) : _hmd(hmd)
{
    std::cout << "init ui controller" << endl;
    showMenu = true;
    menuSize = cv::Size2i(400, 400);
    menuPos = cv::Point2i(DEFAULT_UI_SIZE_X - menuSize.width, (DEFAULT_UI_SIZE_Y / 2) - (menuSize.height / 2)); // centered right
    selectedIndex = 0;
    menuItemNames = {"set vr mode", "set cinema mode", "settings", "quit"};
    unsigned int i = 0;
    update();
    buildMenu();
    cout << "done init ui controller" << endl;
}

void UiController::Update(const std::string &key, const std::string &value)
{
    unsigned int ukey;
    unsigned int uvalue;
    try{ ukey = std::stoul(key);}catch(Exception e){}
    if((InputTypes)ukey != InputTypes::KEYBOARD) return;
    try{ uvalue = std::stoul(value);}catch(Exception e){}
    switch ((KeyboardKeyCode)uvalue)
    {
    case KeyboardKeyCode::UP_ARROW:
        DEBUG_LOG(c << "++");
        menus[_activeMenu]->selectedUp();
        break;
    case KeyboardKeyCode::DOWN_ARROW:
        DEBUG_LOG(c << "--");
        cout << _activeMenu << endl;
        menus[_activeMenu]->selectedDown();
        break;
    case KeyboardKeyCode::LEFT_ARROW: // 1
        DEBUG_LOG(c << "1");
        menus[_activeMenu]->clickback();
        break;
    case KeyboardKeyCode::NUM_0: //<
        DEBUG_LOG(c << "2");
        menus[_activeMenu]->clickb1();
        break;
    case KeyboardKeyCode::NUM_1: //>
        DEBUG_LOG(c << "3");
        menus[_activeMenu]->clickb2();
        break;
    case KeyboardKeyCode::RIGHT_ARROW: // 2
        DEBUG_LOG(c << "0");
        menus[_activeMenu]->clickok();
        break;
    default:
        cout << uvalue << endl;
        break;
    }
}

void UiController::update()
{
    time_t now = time(0);
    menutime = ctime(&now);
    menuTitle = std::string("P-OS ") + VERSION + " " + menutime;
}

void UiController::buildMenu()
{
    menus.clear();
    _activeMenu = "main menu";
#pragma region main_menu

    ExitAppCommand *ex = new ExitAppCommand();

    Command *navigateToMain = new NavigateCommand(_activeMenu, this);
    Menu *main = new Menu(_activeMenu, main, navigateToMain); // it's the root so it navigates back to itself
    menus[main->getName()] = main;

    ButtonItem *exitBtn = new ButtonItem(ex);
    exitBtn->setData("exit the app");
    main->addItem(exitBtn);
#pragma endregion main_menu
#pragma region psvr_menu
    Menu *psvrMenu = new Menu("PSVR options", main, navigateToMain);
    menus[psvrMenu->getName()] = psvrMenu;

    Command *navigateToPsvr = new NavigateCommand(psvrMenu->getName(), this);

    menuitem *psvrOptions = new menuitem(navigateToPsvr);
    psvrOptions->setData("open psvr options");

    main->addItem(psvrOptions);

    Command *startup = new StartupCommand(_hmd);
    Command *shutdown = new ShutdownCommand(_hmd);
    Command *vrmode = new VrModeCommand(_hmd);
    Command *cinemamode = new CinemaModeCommand(_hmd);

    ButtonItem *startBtn = new ButtonItem(startup);
    ButtonItem *stopBtn = new ButtonItem(shutdown);
    ButtonItem *vrBtn = new ButtonItem(vrmode);
    ButtonItem *cinemaBtn = new ButtonItem(cinemamode);

    startBtn->setData("startup psvr");
    stopBtn->setData("shutdown psvr");
    vrBtn->setData("set psvr VR mode");
    cinemaBtn->setData("set psvr Cinema mode");

    psvrMenu->addItem(startBtn);
    psvrMenu->addItem(stopBtn);
    psvrMenu->addItem(vrBtn);
    psvrMenu->addItem(cinemaBtn);
#pragma endregion psvr_menu
#pragma region fps_menu
    Menu *fpsMenu = new Menu("EPS options", main, navigateToMain);
    menus[fpsMenu->getName()] = fpsMenu;

    Command *navigateToEPS = new NavigateCommand(fpsMenu->getName(), this);

    menuitem *fpsOptions = new menuitem(navigateToEPS);
    fpsOptions->setData("open EPS options");
    main->addItem(fpsOptions);

    fpsMenu->addItem(new NumberPickerItem("camera EPS limit","fpsLimit",60));  //must be in the same order as when the pipeline is created
    fpsMenu->addItem(new NumberPickerItem("zbar EPS limit","fpsLimit",15));
    fpsMenu->addItem(new NumberPickerItem("ui drawer EPS limit","fpsLimit",30));
    fpsMenu->addItem(new NumberPickerItem("ui merger EPS limit","fpsLimit",60));
    fpsMenu->addItem(new NumberPickerItem("display EPS limit","fpsLimit",60));

#pragma endregion fps_menu
#pragma region video_recording_menu
    Menu *viderecMenu = new Menu("Media capture", main, navigateToMain);
    menus[viderecMenu->getName()] = viderecMenu;

    Command *navigateTovidrec = new NavigateCommand(viderecMenu->getName(), this);

    menuitem *vidrecItem = new menuitem(navigateTovidrec);
    vidrecItem->setData("media capture");
    main->addItem(vidrecItem);
#pragma endregion video_recording_menu
}