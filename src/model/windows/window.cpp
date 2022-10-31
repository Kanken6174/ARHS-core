#include "window.hpp"

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
      cv::imshow(this->myWindow, this->drawTexture);
   #else
      cv::imshow(this->myWindow, drawBuffer);
   #endif
      cv::waitKey(10);
   }
   catch(...){
      drawAccess.unlock();
   }
}