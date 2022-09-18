#include<iostream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include <functional>

#include "../cameras/_cam.hpp"
#include "../psvr/_psvr.hpp"
#include <opencv2/imgcodecs/imgcodecs.hpp>

#define DEFAULT_UI_WINDOW_AMOUNT 2  //2 windows, one for each eye
#define DEFAULT_UI_OFFSET_X 0    //1080
#define DEFAULT_UI_OFFSET_Y 0
#define DEFAULT_UI_SIZE_X 960   //psvr is 960x1080 per eye
#define DEFAULT_UI_SIZE_Y 1080

int runtest();

using namespace std;
using namespace cv;
using namespace psvr;

namespace ui {
    //Defines a single ui window (by default two will be displayed)
    class Ui{
        public:
        Mat drawSurface; //Current frame 
        std::string myWindow;
        void draw();
    };
    class UiDrawer{ //drawer is static because we only ever need one
        public:
        static void drawUiR();
        static void drawUiL();
        static void drawStartupSequence();
        static void drawMenu();
        static Mat OverlayMat;  //drawn at each frame
        static Mat OsMat;   //drawn on certain events
        static std::mutex OsMatLock;
        private:
        static Mat prepareUiMat();
        static Mat resizeIn(Mat input);
        static Mat OverlayBlackMask(Mat input, Mat toOverlay, int x = 0, int y = 0);
        static Mat OverlayHISHMask(Mat input, Mat toOverlay);
    };
        class UiManager{ //manager is static because we only ever need one
        public:
        static vector<Ui*> managedUIs;
        static void init();
        static void cleanup();       
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
