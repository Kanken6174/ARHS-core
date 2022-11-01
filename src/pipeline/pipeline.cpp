#include "pipeline.hpp"
#include "./../model/windows/windowManager.hpp"
#include "../model/hardware/hw/serial.hpp"
#include "./members/subNodes/subNodes.hpp"

Pipeline::Pipeline(){
    WindowManager* wm = new WindowManager();
    cameraManager* cm = new cameraManager();
    cm->runCapture();
    psvr::Psvr* hmd = new psvr::Psvr();
    UiController* uc = new UiController(hmd);
    SerialPortManager* sp = new SerialPortManager();
    
    sp->Attach(uc);

    FpsCounter* fc = new FpsCounter();
    StaticImageOverlayer* sio = new StaticImageOverlayer();
    sio->setImage("./media/hud_fixed.png");
    
    zbarScanner* zs = new zbarScanner();
    ZbarOverlayer* zo = new ZbarOverlayer(zs);

    nodes.push_back(new cameraPickerNode(cm));
    nodes.push_back(new ZbarAnalysisNode(nodes.at(0), zs));
    nodes.push_back(new UiDrawerNode(uc));
    nodes.at(2)->addSubNode(fc);
    nodes.at(2)->addSubNode(sio);
    nodes.at(2)->addSubNode(zo);
    nodes.at(2)->fpsLimit = 30;
    nodes.push_back(new UiMergerNode(nodes.at(0),nodes.at(2),uc));
    nodes.push_back(new DisplayOutputNode(nodes.at(3), wm->managedUIs.at(0)));

    for(PipelineNode* pn : nodes)
        fc->addChecker(pn->getName(),pn->localES);

    for(PipelineNode* pn : nodes)
        pn->start();

}