#include "_ui.hpp"

void ui::Ui::draw(){
   if(drawSurface.empty())
      return;
   imshow(this->myWindow, this->drawSurface);
   waitKey(1);
}