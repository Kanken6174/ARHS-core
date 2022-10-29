#include<iostream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include <functional>

#include <GL/glut.h>

#include "../cameras/_cam.hpp"
#include "../psvr/_psvr.hpp"
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/opengl.hpp>

#define DEFAULT_UI_WINDOW_AMOUNT 1  //2 windows, one for each eye
#define DEFAULT_UI_OFFSET_X 1080    //1080
#define DEFAULT_UI_OFFSET_Y 0
#define DEFAULT_UI_SIZE_X 1920   //psvr is 960x1080 per eye
#define DEFAULT_UI_SIZE_Y 1080

int runtest();

using namespace std;
using namespace cv;
using namespace cv::ogl;
using namespace psvr;

namespace ui {
    /// @brief this class represents a single window, there should only ever be one if the app is in opengl mode.
    class Ui{
        public:
        UMat drawSurface; //Current frame 
        cv::ogl::Texture2D drawTexture = Texture2D();
        int id;
        std::string myWindow;
        void draw();
    };
    class UiSupport{
        public:
        static UMat makeMatStereo(UMat toStereo);
        static UMat prepareUiMat();
        static UMat resizeIn(UMat input);
        static UMat OverlayBlackMask(UMat input, UMat toOverlay, int x = 0, int y = 0);
    };
    /// @brief this class is used to draw the UI from the UiController's current state
    class UiDrawer{
        public:
        static void drawStartupSequence();
        static void drawMenu();
        static void runDrawMenu();
        static UMat output;
        static std::mutex outputLock;
        static framerateChecker* fpsCounter;
        private:
        static void drawUi();
    };
    /// @brief this class is used to merge the camera's frame and the UI mat
    class UiMerger{
        public: 
        static void runMerge();
        static UMat output;
        static std::mutex outputLock;
        private:
        static void mergeUI();
    };
    /// @brief this class manages the UI(s) [windows] used by the application, right now only one should ever be used, especially in opengl mode
    class UiManager{
        public:
        static vector<mutex*> accessLocks;
        static vector<Ui*> managedUIs;
        static bool uiShouldRun;
        static void init();
        static void cleanup();
        static void beginDrawRoutineForUi(Ui* u);     
    };
    /// @brief this class is used to process view logic and interaction [model]
    class UiController{
        public:
        static void init();
        static void selectedUp();
        static void selectedDown();
        static void click();
        static void update();
        static void openSettings();
        static vector<std::string> menuItemNames;
        static bool showMenu;
        static bool exitCalled;
        static bool runIntro;
        static string menuTitle;
        static cv::Size2i menuSize;
        static cv::Point2i menuPos;
        static unsigned int selectedIndex;
        static map<std::string, std::function<void()>> menuItems;
        static char* menutime;
    };

}
