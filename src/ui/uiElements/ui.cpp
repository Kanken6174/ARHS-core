#include "../_ui.hpp"

void ui::Ui::draw(){
   try{
   DEBUG_LOG("\nBegin drawing--------------")
   fcheckManager::fcShow.tickBegin();
   UiManager::accessLocks.at(this->id)->lock();   
   if(drawSurface.empty()){
      UiManager::accessLocks.at(this->id)->unlock();
      return;
   }
   UMat drawBuffer = drawSurface;
   UiManager::accessLocks.at(this->id)->unlock();
   DEBUG_LOG("Buffer retreived")
   #ifdef OGLWIN
      drawTexture.copyFrom(drawBuffer);
      imshow(this->myWindow, this->drawTexture);
   #else
      imshow(this->myWindow, drawBuffer);
   #endif

   waitKey(10);
   fcheckManager::fcShow.tickUpdate();
   DEBUG_LOG("Done draw cycle-----------------")
   }
   catch(...){
      cerr << "exception caught in ui::draw" << endl;
      UiManager::accessLocks.at(this->id)->unlock();
   }
}