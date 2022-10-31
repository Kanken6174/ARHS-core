#include "windowManager.hpp"
#include <thread>
    // initializes the ui manager, following default values
    WindowManager::WindowManager()
    {
        uiShouldRun = false;
        for (int i = 0; i < DEFAULT_UI_WINDOW_AMOUNT; i++)
        {
            Window *newWindow = new Window();
            newWindow->myWindow = "project- UI" + std::to_string(i);
#ifndef OGLWIN
            cv::namedWindow(newWindow->myWindow);   //if we're in opengl mode, the window needs to be created in the same thread as the execution, not here
#endif
            cv::moveWindow(newWindow->myWindow, DEFAULT_UI_OFFSET_X + i * 960, DEFAULT_UI_OFFSET_Y);
            cv::resizeWindow(newWindow->myWindow, DEFAULT_UI_SIZE_X, DEFAULT_UI_SIZE_Y);

            //cout << "window: " << newWindow->myWindow << " created at " << DEFAULT_UI_OFFSET_X + i * 960 << " , " << DEFAULT_UI_OFFSET_Y << endl;

            newWindow->id = i;

            managedUIs.push_back(newWindow); // add new ui in the ui map, mapped to the window's name
        }
        uiShouldRun = true;
    }

    void WindowManager::cleanup()
    {
    }