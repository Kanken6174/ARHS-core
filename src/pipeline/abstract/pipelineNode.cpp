#include "pipelineNode.hpp"

bool PipelineNode::isRunning()
{
    return this->shouldRun;
}

bool PipelineNode::isDependant(){
    return previous != nullptr;
}

void PipelineNode::stop()
{
    this->shouldRun = false;
}

cv::UMat PipelineNode::getOutput()
{
    const std::lock_guard<std::mutex> lock(outputLock);
    return output;
}

void PipelineNode::run()
{
    try
    {
        this->shouldRun = true;
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        while (this->shouldRun)
        {
            begin = std::chrono::steady_clock::now();
                localES.tickBegin();
                    this->processFrame();
                localES.tickUpdate();
            end = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(std::chrono::milliseconds((1000 / this->fpsLimit) - std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()));
        }
    }
    catch (...)
    {
        exit(1);
    }
}