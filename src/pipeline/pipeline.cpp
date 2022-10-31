#include "pipeline.hpp"
#include "../../model/windows/windowManager.hpp"

Pipeline::Pipeline(){
    WindowManager* wm = new WindowManager();
    cameraManager* cm = new cameraManager();
    UiController* uc = new UiController();

    nodes.push_back(new cameraPickerNode(cm));
    nodes.push_back(new UiDrawerNode());
    nodes.push_back(new UiMergerNode(nodes.at(0),nodes.at(1),uc));
    nodes.push_back(new DisplayOutputNode(nodes.at(2), wm->managedUIs.at(0)));
}