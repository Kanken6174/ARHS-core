#include "pipeline.hpp"
#include "./../model/windows/windowManager.hpp"
#include "../model/hardware/hw/serial.hpp"

Pipeline::Pipeline(){
    WindowManager* wm = new WindowManager();
    cameraManager* cm = new cameraManager();
    cm->runCapture();
    psvr::Psvr* hmd = new psvr::Psvr();
    UiController* uc = new UiController(hmd);
    SerialPortManager* sp = new SerialPortManager();
    
    sp->Attach(uc);

    nodes.push_back(new cameraPickerNode(cm));
    nodes.push_back(new UiDrawerNode(uc));
    nodes.push_back(new UiMergerNode(nodes.at(0),nodes.at(1),uc));
    nodes.push_back(new DisplayOutputNode(nodes.at(2), wm->managedUIs.at(0)));

    for(PipelineNode* pn : nodes)
        pn->start();
}