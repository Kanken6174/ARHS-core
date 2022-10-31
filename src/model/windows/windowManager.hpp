#include "window.hpp"
#include <vector>

#define DEFAULT_UI_WINDOW_AMOUNT 1  //2 windows, one for each eye
#define DEFAULT_UI_OFFSET_X 1080    //1080
#define DEFAULT_UI_OFFSET_Y 0
#define DEFAULT_UI_SIZE_X 1920   //psvr is 960x1080 per eye
#define DEFAULT_UI_SIZE_Y 1080

/// @brief this class manages the UI(s) [windows] used by the application, right now only one should ever be used, especially in opengl mode
class WindowManager
{
public:
    std::vector<Window *> managedUIs;
    bool uiShouldRun;
    WindowManager();
    void cleanup();
};