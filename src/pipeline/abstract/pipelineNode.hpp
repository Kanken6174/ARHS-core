#pragma once
#include <mutex>
#include <opencv2/core.hpp>
#include <atomic>
#include <thread>
#include <ios>
#include <thread>

#include "../../model/perfcheckers/framerate.hpp"
#include "../../threadweaver/threadweaver.hpp"
#include "../../model/controllers/ui/uiController.hpp"


/// @brief this class represents an unthreaded sub-node of a given node of the graphcis pipeline
class SubNode{
    public:
    virtual void processFrame(cv::UMat& input, cv::Point2d& cursorPos)=0;
    std::atomic_bool enabled = true;
};

/// @brief this class represents a threaded node of the graphics pipeline
class PipelineNode : public MapObserver{
    public:
        PipelineNode();
        std::atomic_int fpsLimit = 60;
        framerateChecker* localES;
        cv::UMat getOutput();
        void run();
        bool isRunning();
        void stop();
        void start();
        virtual std::string getName()=0;
        std::thread* joinThread();
        void setThreadToCore(int core);
        void addSubNode(SubNode* sn);
        //virtual ~PipelineNode();
        float cost = 1;
        std::mutex outputLock;
        std::mutex subNodesLock;
        std::atomic_bool disabled = false;  //if true short circuit your input to your output
        std::atomic_bool changed = true;    //specifies if the output has changed since last frame grab
        void Update(const std::string &key, const std::string &value) override{
        if(key == "fpsLimit")
            this->fpsLimit = stoi(value);
        }
    protected:
        std::vector<SubNode*> subNodes;
        cv::UMat output;
        std::atomic_bool shouldRun = false;
        std::atomic_bool isLast = true;     //needs to be changed by the implementing classes
        std::atomic_bool isFirst = true;    //needs to be changed by the implementing classes
        std::atomic_bool ranOnce = false;
        PipelineNode* previous = nullptr;   //represents the previous PipelineNode in the hierarchy, it is the original umat source
        std::thread* localThread;           //represents the local thread for this node
        virtual void processFrame()=0;
};