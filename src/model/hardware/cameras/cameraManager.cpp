#include "_cam.hpp"
#include <signal.h>

void cameraManager::runCaptureForCamera(camera* c, uint index){
    while(runCaptureThread){
        if(!c->source->isOpened()){
            cout << "camera " << c->path << " is closed, opening..." << endl;
            if(!c->source->open(c->path)){
                cout << "couldn't open camera with index " << c->path << endl;
            }else{
                c->source->set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
                c->source->set(CV_CAP_PROP_FPS , FPS_LIMIT_PSEYE);
            }
        }

        if(c->source->grab()){
            UMat surface;
            c->source->retrieve(surface);
            accessLocks[index]->lock();
            captures[index] = surface;
            accessLocks[index]->unlock();
        } else {
            cout << "read error grabbing from camera " << c->path << endl;
        }
    }
}

cameraManager::cameraManager(){
    std::cout << "init camera manager" << endl;
    vector<std::string> cameras = listCameras();
    uint cameraIndex = 0;
    std::cout << "found " << cameras.size() << " cameras" << endl;

    for(string camIdx : cameras)    //camera input testing
    {
        int camID = stoi(camIdx);
        try{
            VideoCapture vs(camID);
            if(!vs.isOpened() && !vs.open(camID))
            {
                cout << "\x1B[31opening camera " << camIdx << " failed\033[0m" <<endl;
                vs.release();
            }else{
            vs.release();
            camera* cam = new camera();
            cam->source = new VideoCapture(camID, CAP_FFMPEG);
            cam->source->set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
            cam->source->set(CV_CAP_PROP_FPS , FPS_LIMIT_PSEYE);
            cam->source->set(CAP_PROP_FRAME_WIDTH, 1920);
            cam->source->set(CAP_PROP_FRAME_HEIGHT, 1080);
            

            cam->path = camID;
            videoSources.push_back(cam);    //valid camera added
            cout << "added camera with path /dev/video" << cam->path << endl;
            UMat m;
            captures.push_back(std::move(m));             
            }
        }
        catch(exception e){
            cout << e.what() << endl;
        }
    }

    cout << "found " << std::to_string(videoSources.size()) << " valid cameras" << endl;
}

void cameraManager::runCapture(){
    cout << "cameraManager::runCapture------------------------------------------------\n" << "enabling capture thread for " << videoSources.size() << " cameras" << endl;
    uint i = 0;
    runCaptureThread = true;
    for(camera* c : videoSources){
        mutex* mlock = new mutex();
        mlock->unlock();
        accessLocks.push_back(mlock);
        cout << "enabling camera " << i << endl;
        c->source->release();
        std::thread* t = new std::thread(&cameraManager::runCaptureForCamera,this,c,i);   //TODO fix thread handling
        i++;
        cout << "moving thread" << endl;
        Threadweaver::stick_this_thread_to_core(t,CAMCORE);
        //Threadweaver::captureThreads.push_back(t);
        cout << "done" << endl;
    }
    cout << "done enabling threads" << endl;
}

void cameraManager::stopCapture(){
    runCaptureThread = false;
    /*for(std::thread* t : Threadweaver::captureThreads){
        t->join();
        delete t;
    }*/
    //Threadweaver::captureThreads.clear();
    for(std::mutex* mlock : accessLocks){
        mlock->unlock();
        delete mlock;
    }
    accessLocks.clear();
}