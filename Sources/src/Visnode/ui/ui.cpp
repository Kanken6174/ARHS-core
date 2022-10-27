#include "_ui.hpp"

void ui::Ui::draw(){
   try{
   DEBUG_LOG("\nBegin drawing--------------")
   fcheckManager::fcShow.tickBegin();
   UiManager::accessLocks.at(this->id)->lock();   
   if(drawSurface.empty()){
      UiManager::accessLocks.at(this->id)->unlock();
      return;
   }
   #ifdef OGLWIN
      DEBUG_LOG("Assigning opengl buffer")
      UMat drawBuffer = drawSurface;   //required copy?
      DEBUG_LOG("Done assigning opengl buffer")
   #else
      UMat drawBuffer = drawSurface;
   #endif
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