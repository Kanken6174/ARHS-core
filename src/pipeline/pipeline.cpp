#include "pipeline.hpp"
#include "./../model/windows/windowManager.hpp"
#include "./members/subNodes/subNodes.hpp"
#include "../pluginManagement/PluginManager.hpp"

Pipeline::Pipeline()
{
    WindowManager *wm = new WindowManager();
    cameraManager *cm = new cameraManager();
    cm->runCapture();
    psvr::Psvr *hmd = new psvr::Psvr();
    UiController *uc = new UiController(hmd);
    SerialPortManager *sp = new SerialPortManager();

    sp->Attach(uc);

    FpsCounter *fc = new FpsCounter();
    StaticImageOverlayer *sio = new StaticImageOverlayer();
    sio->setImage("./media/hud_fixed.png");

    zbarScanner *zs = new zbarScanner();
    ZbarOverlayer *zo = new ZbarOverlayer(zs);

    cameraPickerNode *cpn = new cameraPickerNode(cm);
    VideoCaptureNode *vcn = new VideoCaptureNode(cpn);
    ZbarAnalysisNode *zban = new ZbarAnalysisNode(cpn, zs);
    UiDrawerNode *udn = new UiDrawerNode(uc);
        udn->addSubNode(fc);
        udn->addSubNode(sio);
        udn->addSubNode(zo);
        udn->fpsLimit = 30;
    UiMergerNode* umn = new UiMergerNode(cpn, udn, uc);
    DisplayOutputNode* don = new DisplayOutputNode(umn, wm->managedUIs.at(0));

    nodes.push_back(cpn);
    nodes.push_back(vcn);
    nodes.push_back(zban);
    nodes.push_back(udn);
    nodes.push_back(umn);
    nodes.push_back(don);

    zban->disabled = false;  //disable the zbar node by default

    Menu *epsMenu = uc->getSpecificMenu("EPS options"); // create menu for execution per second limits

    for (int i = 0; i < nodes.size() && i < epsMenu->getItems().size(); i++) // each node subscribes to the menu and adds its item
        epsMenu->getItems().at(i)->Attach(nodes.at(i));

    Menu *mediaMenu = uc->getSpecificMenu("Media capture");

    VideoCaptureStartCommand *vcstart = new VideoCaptureStartCommand(vcn);
    VideoCaptureStopCommand *vcstop = new VideoCaptureStopCommand(vcn);
    PictureSnapCommand *vcsnap = new PictureSnapCommand(vcn);

    ButtonItem* vcstartBtn = new ButtonItem(vcstart);
    vcstartBtn->setData("start capture");
    ButtonItem* vcstopBtn = new ButtonItem(vcstop);
    vcstopBtn->setData("stop capture");
    ButtonItem* vcsnapBtn = new ButtonItem(vcsnap);
    vcsnapBtn->setData("snapshot");

    mediaMenu->addItem(vcstartBtn);
    mediaMenu->addItem(vcstopBtn);
    mediaMenu->addItem(vcsnapBtn);

    PluginManager(*this);

    startPipeline();

    for (PipelineNode *pn : nodes)
        fc->addChecker(pn->getName(), pn->localES);
}

void Pipeline::startPipeline()
{

    for (PipelineNode *pn : nodes)
        pn->start();
}