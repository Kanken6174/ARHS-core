#include "pipeline.hpp"
#include "./../model/windows/windowManager.hpp"
#include "../model/hardware/hw/serial.hpp"
#include "./members/subNodes/fpsCounter.hpp"

Pipeline::Pipeline(){
    WindowManager* wm = new WindowManager();
    cameraManager* cm = new cameraManager();
    cm->runCapture();
    psvr::Psvr* hmd = new psvr::Psvr();
    UiController* uc = new UiController(hmd);
    SerialPortManager* sp = new SerialPortManager();
    
    sp->Attach(uc);

    FpsCounter* fc = new FpsCounter();

    nodes.push_back(new cameraPickerNode(cm));
    nodes.push_back(new UiDrawerNode(uc));
    nodes.at(1)->addSubNode(fc);
    nodes.push_back(new UiMergerNode(nodes.at(0),nodes.at(1),uc));
    nodes.push_back(new DisplayOutputNode(nodes.at(2), wm->managedUIs.at(0)));

    fc->addChecker("camera picker",nodes.at(0)->localES);
    fc->addChecker("ui drawer",nodes.at(1)->localES);
    fc->addChecker("ui merger",nodes.at(2)->localES);
    fc->addChecker("display output",nodes.at(3)->localES);

    for(PipelineNode* pn : nodes)
        pn->start();
}