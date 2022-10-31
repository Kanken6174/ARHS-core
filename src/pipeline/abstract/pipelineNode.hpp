#pragma once
#include <mutex>
#include <opencv2/core.hpp>
#include <atomic>
#include <thread>
#include <ios>
#include "../../model/perfcheckers/framerate.hpp"

class PipelineNode{
    public:
        std::atomic_int fpsLimit = 60;
        framerateChecker localES;
        cv::UMat getOutput();
        void run();
        bool isRunning();
        bool isDependant();
        void stop();
        //virtual ~PipelineNode();
        float cost = 1;
    protected:
        virtual void processFrame();
        std::mutex outputLock;
        cv::UMat output;
        std::atomic_bool shouldRun;
        std::atomic_bool  disabled;
        PipelineNode* previous;
};