#include "window.hpp"
#include "../hardware/hw/inputManager.hpp"
void glDrawTextureCallback(void* userdata)
{
   cv::ogl::Texture2D* texObj = static_cast<cv::ogl::Texture2D*>(userdata);
   cv::ogl::render(*texObj);
}

Window::Window(std::string windowName){
   this->myWindow = windowName;
}

void Window::glInit(){
   cv::namedWindow(this->myWindow, cv::WINDOW_OPENGL);
   setWindowProperty(this->myWindow, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
   cv::setOpenGlContext(this->myWindow);
   cv::moveWindow(this->myWindow, DEFAULT_UI_OFFSET_X + 960, DEFAULT_UI_OFFSET_Y);
   cv::setOpenGlContext(this->myWindow);
   cv::setOpenGlDrawCallback(this->myWindow, glDrawTextureCallback, &this->drawTexture);
}

void Window::draw(){
   try{
   drawAccess.lock();   
   if(drawSurface.empty()){
      drawAccess.unlock();
      return;
   }
   cv::UMat drawBuffer = drawSurface;
   drawAccess.unlock();

   #ifdef OGLWIN
      drawTexture.copyFrom(drawBuffer);
      cv::updateWindow(this->myWindow);
   #else
      cv::imshow(this->myWindow, drawBuffer);
   #endif
      int key = cv::waitKey(1);
      if (key >= 0) {
        InputManager::GetInstance()->sendinput(key, InputTypes::KEYBOARD);
    }
   }
   catch(...){
      drawAccess.unlock();
      std::cout << "Caught draw window thread exception" << std::endl;
   }
}