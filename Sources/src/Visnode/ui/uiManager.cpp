#include "_ui.hpp"

namespace ui{
    vector<Ui*> UiManager::managedUIs;
    vector<mutex*> UiManager::accessLocks;
    bool UiManager::uiShouldRun;

    void UiManager::beginDrawRoutineForUi(Ui* u){
        while(!ui::UiManager::uiShouldRun){}
        while(ui::UiManager::uiShouldRun){
            u->draw();
        }
    }

    //initializes the ui manager, following default values
    void UiManager::init(){
        uiShouldRun = false;
        waitKey(1);
        for(int i=0; i<DEFAULT_UI_WINDOW_AMOUNT; i++){
            Ui* newUI = new Ui();
            cout << "creating UI n°" << to_string(i) << endl;
            newUI->myWindow = "project- UI"+std::to_string(i);
            
            namedWindow(newUI->myWindow);
            moveWindow(newUI->myWindow,DEFAULT_UI_OFFSET_X+i*960,DEFAULT_UI_OFFSET_Y);
            resizeWindow(newUI->myWindow,DEFAULT_UI_SIZE_X,DEFAULT_UI_SIZE_Y);
            setWindowProperty(newUI->myWindow, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

            cout << "window: " << newUI->myWindow << " created at " << DEFAULT_UI_OFFSET_X+i*960 << " , " << DEFAULT_UI_OFFSET_Y << endl;

            newUI->id = i;

            managedUIs.push_back(newUI);   //add new ui in the ui map, mapped to the window's name
            accessLocks.push_back(new mutex());
            accessLocks.at(i)->unlock();
            std::thread* t = new std::thread(ui::UiManager::beginDrawRoutineForUi,newUI);
            Threadweaver::stick_this_thread_to_core(t,0);
            Threadweaver::osUiDrawerThread = t; //TODO fix?
        }
        uiShouldRun = true;
    }

    void UiManager::cleanup(){

    }
}