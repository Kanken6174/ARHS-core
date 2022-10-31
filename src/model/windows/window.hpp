#include <opencv2/core/core.hpp>
#include <opencv2/core/opengl.hpp>
#include <opencv2/highgui.hpp>
#include <GL/glut.h>
#include <mutex>

/// @brief this class represents a single window, there should only ever be one if the app is in opengl mode.
class Window
{
public:
    cv::UMat drawSurface; // Current frame
    cv::ogl::Texture2D drawTexture = cv::ogl::Texture2D();
    int id;
    std::mutex drawAccess;
    std::string myWindow;
    void draw();
};