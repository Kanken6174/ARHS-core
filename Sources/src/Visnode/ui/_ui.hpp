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
    //Defines a single ui window (by default two will be displayed)
    class Ui{
        public:
        UMat drawSurface; //Current frame 
        cv::ogl::Texture2D drawTexture = Texture2D();
        int id;
        bool inited = false;
        std::string myWindow;
        void draw();
    };
    class UiDrawer{ //drawer is static because we only ever need one
        public:
        static void drawUi();
        static void drawStartupSequence();
        static void drawMenu();
        static void runDrawUi();
        static UMat OverlayMat;  //drawn at each frame (screen)
        static UMat OsMat;   //drawn on certain events (menu)
        static cv::ogl::Texture2D OvTexture;
        static std::mutex OsMatLock;
        private:
        static framerateChecker* fpsCounter;
        static UMat prepareUiMat();
        static UMat resizeIn(UMat input);
        static UMat OverlayBlackMask(UMat input, UMat toOverlay, int x = 0, int y = 0);
        static UMat OverlayHISHMask(UMat input, UMat toOverlay);
    };
        class UiManager{ //manager is static because we only ever need one
        public:
        static vector<mutex*> accessLocks;
        static vector<Ui*> managedUIs;
        static bool uiShouldRun;
        static void init();
        static void cleanup();
        static void beginDrawRoutineForUi(Ui* u);     
    };
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
