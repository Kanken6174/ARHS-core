#include "_ui.hpp"

void ui::Ui::draw(){
   if(drawSurface.empty())
      return;
   UiManager::accessLocks.at(this->id)->lock();   
   drawBuffer = drawSurface;
   UiManager::accessLocks.at(this->id)->unlock(); 
   
   imshow(this->myWindow, this->drawBuffer);
   waitKey(17);
}