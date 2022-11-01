#pragma once
#include <mutex>
#include <opencv2/core.hpp>
#include <atomic>
#include <thread>
#include <ios>
#include <thread>

#include "../../model/perfcheckers/framerate.hpp"
#include "../../threadweaver/threadweaver.hpp"

class PipelineNode{
    public:
        PipelineNode();
        std::atomic_int fpsLimit = 60;
        framerateChecker localES;
        cv::UMat getOutput();
        void run();
        bool isRunning();
        void stop();
        void start();
        std::thread* joinThread();
        void setThreadToCore(int core);
        //virtual ~PipelineNode();
        float cost = 1;
    protected:
        std::mutex outputLock;
        cv::UMat output;
        std::atomic_bool shouldRun = false;
        std::atomic_bool disabled = false;  //if true short circuit your input to your output
        std::atomic_bool isLast = true;     //needs to be changed by the implementing classes
        std::atomic_bool isFirst = true;    //needs to be changed by the implementing classes
        std::atomic_bool ranOnce = false;
        PipelineNode* previous = nullptr;   //represents the previous PipelineNode in the hierarchy, it is the original umat source
        std::thread* localThread;           //represents the local thread for this node
        virtual void processFrame()=0;
};