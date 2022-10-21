#include "_ui.hpp"

void ui::Ui::draw(){
   fcheckManager::fcShow.tickBegin();
   UiManager::accessLocks.at(this->id)->lock();   
   if(drawSurface.empty()){
      UiManager::accessLocks.at(this->id)->unlock();
      return;
   }
   drawBuffer = drawSurface;
   UiManager::accessLocks.at(this->id)->unlock();
   #ifdef OGLWIN
      UMat blk1920x1080(cv::Size(1920, 1080), CV_8UC3,Scalar(0,0,0));
      drawTexture = Texture2D(1920,1080,cv::ogl::Texture2D::Format::RGBA,false);
      //cv::ogl::convertToGLTexture2D(drawBuffer, drawTexture);
      //imshow(this->myWindow, this->drawTexture);
   #else
      imshow(this->myWindow, this->drawBuffer);
   #endif

   waitKey(10);
   fcheckManager::fcShow.tickUpdate();
}