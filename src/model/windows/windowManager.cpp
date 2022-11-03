#include "windowManager.hpp"
#include <thread>
    // initializes the ui manager, following default values
    WindowManager::WindowManager()
    {
        try{
        uiShouldRun = false;
        for (int i = 0; i < DEFAULT_UI_WINDOW_AMOUNT; i++)
        {
            Window *newWindow;
            std::string name = "project- UI" + std::to_string(i);
#ifndef OGLWIN
            cv::namedWindow(name);   //if we're in opengl mode, the window needs to be created in the same thread as the execution, not here
            cv::moveWindow(name, DEFAULT_UI_OFFSET_X + i * 960, DEFAULT_UI_OFFSET_Y);
            cv::resizeWindow(name, DEFAULT_UI_SIZE_X, DEFAULT_UI_SIZE_Y);
#endif
            newWindow = new Window(name);

            //cout << "window: " << newWindow->myWindow << " created at " << DEFAULT_UI_OFFSET_X + i * 960 << " , " << DEFAULT_UI_OFFSET_Y << endl;

            newWindow->id = i;

            managedUIs.push_back(newWindow); // add new ui in the ui map, mapped to the window's name
        }
        uiShouldRun = true;
        }
        catch(std::exception& e){
            std::cerr << "\033[1;31m caught windowManager::WindowManager thread exception: " << e.what() <<" \033[0m" << std::endl;
        }
    }

    void WindowManager::cleanup()
    {
    }