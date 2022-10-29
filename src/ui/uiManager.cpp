#include "_ui.hpp"

namespace ui{
    vector<Ui*> UiManager::managedUIs;
    vector<mutex*> UiManager::accessLocks;
    bool UiManager::uiShouldRun;

    void UiManager::beginDrawRoutineForUi(Ui* u){
        #ifdef OGLWIN
        namedWindow(u->myWindow,WINDOW_OPENGL);
        setWindowProperty(u->myWindow, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
        cv::setOpenGlContext(u->myWindow);
        moveWindow(u->myWindow,DEFAULT_UI_OFFSET_X+960,DEFAULT_UI_OFFSET_Y);
        resizeWindow(u->myWindow,DEFAULT_UI_SIZE_X,DEFAULT_UI_SIZE_Y);
        ui::UiDrawer::drawStartupSequence();
        #endif
        while(!ui::UiManager::uiShouldRun){}
        while(ui::UiManager::uiShouldRun){
            u->draw();
        }
    }

    void on_opengl(void* param)
{
    glLoadIdentity();
    glTranslated(0.0, 0.0, -1.0);
    glRotatef( 55, 1, 0, 0 );
    glRotatef( 45, 0, 1, 0 );
    glRotatef( 0, 0, 0, 1 );
    static const int coords[6][4][3] = {
        { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
        { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
        { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
        { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
        { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
        { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
    };
    for (int i = 0; i < 6; ++i) {
                glColor3ub( i*20, 100+i*10, i*42 );
                glBegin(GL_QUADS);
                for (int j = 0; j < 4; ++j) {
                        glVertex3d(0.2 * coords[i][j][0], 0.2 * coords[i][j][1], 0.2 * coords[i][j][2]);
                }
                glEnd();
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
            #ifdef OGLWIN
                DEBUG_LOG("created opengl window")
                
                //cv::setOpenGlContext(newUI->myWindow);
                //setOpenGlDrawCallback(newUI->myWindow, on_opengl);
            #else
                DEBUG_LOG("created cpu-based window")
                namedWindow(newUI->myWindow);
            #endif
            moveWindow(newUI->myWindow,DEFAULT_UI_OFFSET_X+i*960,DEFAULT_UI_OFFSET_Y);
            resizeWindow(newUI->myWindow,DEFAULT_UI_SIZE_X,DEFAULT_UI_SIZE_Y);
            //setWindowProperty(newUI->myWindow, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

            cout << "window: " << newUI->myWindow << " created at " << DEFAULT_UI_OFFSET_X+i*960 << " , " << DEFAULT_UI_OFFSET_Y << endl;

            newUI->id = i;

            managedUIs.push_back(newUI);   //add new ui in the ui map, mapped to the window's name
            accessLocks.push_back(new mutex());
            accessLocks.at(i)->unlock();
            std::thread* t = new std::thread(ui::UiManager::beginDrawRoutineForUi,newUI);
            Threadweaver::stick_this_thread_to_core(t,DISPLAYCORE);
            Threadweaver::osUiDrawerThread = t;
        }
        uiShouldRun = true;
    }

    void UiManager::cleanup(){

    }
}