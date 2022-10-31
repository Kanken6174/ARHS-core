#include<mutex>
#include <opencv2/core.hpp>

class PipelineMember{
    public:
        virtual void run();
        virtual bool isRunning();
        virtual void stop();
        virtual cv::UMat getOutput();
    protected:
        std::mutex outputLock;
        cv::UMat output;
        bool shouldRun;
        PipelineMember* previous;
};