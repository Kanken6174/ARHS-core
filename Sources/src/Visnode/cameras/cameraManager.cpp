#include "_cam.hpp"

vector<camera*> cameraManager::videoSources;
std::vector<Mat> cameraManager::captures;
bool cameraManager::runCaptureThread;
std::vector<std::mutex*> cameraManager::accessLocks;

void cameraManager::runCaptureForCamera(camera* c, uint index){
    while(runCaptureThread){
        if(!c->source->isOpened()){
            cout << "camera " << c->path << " is closed, opening..." << endl;
            if(!c->source->open(c->path,cv::CAP_ANY)){
                cout << "couldn't open camera with index " << c->path << endl;
            }
        } 

        if(c->source->grab()){
            Mat surface;
            c->source->retrieve(surface);
            cameraManager::accessLocks[index]->lock();
            cameraManager::captures[index] = surface;
            cameraManager::accessLocks[index]->unlock();
        } else {
            cout << "read error grabbing from camera " << c->path << endl;
        }
    }
}

int cameraManager::init(){
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
                cout << "opening camera " << camIdx << " failed" <<endl;
                vs.release();
            }else{
            vs.release();
            camera* cam = new camera();
            cam->source = new VideoCapture(camID);
            cam->path = camID;
            videoSources.push_back(cam);    //valid camera added
            cout << "added camera with path /dev/video" << cam->path << endl;
            Mat m;
            captures.push_back(std::move(m));             
            }
        }
        catch(exception e){
            cout << e.what() << endl;
        }
    }

    cout << "found " << std::to_string(videoSources.size()) << " valid cameras" << endl;
    return videoSources.size();
}

void cameraManager::runCapture(){
    cout << "enabling capture thread for " << videoSources.size() << " cameras" << endl;
    uint i = 0;
    runCaptureThread = true;
    for(camera* c : videoSources){
        mutex* mlock = new mutex();
        mlock->unlock();
        accessLocks.push_back(mlock);
        cout << "enabling camera " << i << endl;
        std::thread* t = new std::thread(cameraManager::runCaptureForCamera,c,i);
        i++;
        cout << "moving thread" << endl;
        Threadweaver::stick_this_thread_to_core(t,i);
        Threadweaver::captureThreads.push_back(t);
        cout << "done" << endl;
    }
    cout << "done enabling threads" << endl;
}

void cameraManager::stopCapture(){
    runCaptureThread = false;
    for(std::thread* t : Threadweaver::captureThreads){
        t->join();
        delete t;
    }
    Threadweaver::captureThreads.clear();
    for(std::mutex* mlock : accessLocks){
        mlock->unlock();
        delete mlock;
    }
    accessLocks.clear();
}