#include "_ui.hpp"

namespace ui{
    vector<Ui*> UiManager::managedUIs;

    //initializes the ui manager, following default values
    void UiManager::init(){
        waitKey(1);
        for(int i=0; i<DEFAULT_UI_WINDOW_AMOUNT; i++){
            Ui* newUI = new Ui();
            cout << "creating UI n°" << to_string(i) << endl;
            newUI->myWindow = "project- UI"+std::to_string(i);
            
            namedWindow(newUI->myWindow);
            moveWindow(newUI->myWindow,DEFAULT_UI_OFFSET_X+i*960,DEFAULT_UI_OFFSET_Y);
            resizeWindow(newUI->myWindow,DEFAULT_UI_SIZE_X,DEFAULT_UI_SIZE_Y);

            cout << "window: " << newUI->myWindow << " created at " << DEFAULT_UI_OFFSET_X+i*960 << " , " << DEFAULT_UI_OFFSET_Y << endl;

            managedUIs.push_back(newUI);   //add new ui in the ui map, mapped to the window's name
        }
    }

    void UiManager::cleanup(){

    }
}