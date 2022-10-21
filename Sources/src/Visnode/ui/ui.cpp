#include "_ui.hpp"

void ui::Ui::draw(){
   fcheckManager::fcShow.tickBegin();
   if(drawSurface.empty()){
      //fcheckManager::fcShow.fps = 0;
      return;
   }
   UiManager::accessLocks.at(this->id)->lock();   
   drawBuffer = drawSurface;
   UiManager::accessLocks.at(this->id)->unlock();
   //drawTexture = cv::ogl::Texture2D(drawBuffer);
   //cv::ogl::convertToGLTexture2D(drawBuffer, drawTexture);
   
   imshow(this->myWindow, this->drawBuffer);
   waitKey(1);
   fcheckManager::fcShow.tickUpdate();
}