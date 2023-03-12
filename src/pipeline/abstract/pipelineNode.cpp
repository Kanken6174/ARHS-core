#include "pipelineNode.hpp"

PipelineNode::PipelineNode()
{
    DEBUG_LOG("pipeline created")
    localES = new framerateChecker();
}

bool PipelineNode::isRunning()
{
    return this->shouldRun;
}

std::thread *PipelineNode::joinThread()
{
    if (isRunning())
        stop();
    return localThread;
}

void PipelineNode::setThreadToCore(int core)
{
    if (core < 0)
        core = std::abs(core);
    while (core > Threadweaver::getCoreCount())
        core = std::abs(core - Threadweaver::getCoreCount());
    Threadweaver::stick_this_thread_to_core(localThread, core);
}

void PipelineNode::stop()
{
    this->shouldRun = false;
}

void PipelineNode::start()
{
    this->shouldRun = true;
    this->localThread = new std::thread(&PipelineNode::run, this);
    DEBUG_LOG("pipeline started on thread " << localThread->get_id())
}

cv::UMat PipelineNode::getOutput()
{
    const std::lock_guard<std::mutex> lock(outputLock);
    changed = false;
    return output;
}

void PipelineNode::addSubNode(SubNode *sn)
{
    const std::lock_guard<std::mutex> lock(subNodesLock);
    subNodes.push_back(sn);
}

void PipelineNode::run()
{
    while (!shouldRun || (!isFirst && (previous == nullptr || previous->ranOnce)))
    {                                                              // sleep until told to run and if you're not the first in your hierarchy,
        std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait for previous to be assigned
    }
    // DEBUG_LOG("pipeline on thread " << localThread->get_id() << " exitted wait while");
    try
    {
        this->shouldRun = true;
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        while (this->shouldRun)
        {
            begin = std::chrono::steady_clock::now();
            localES->tickBegin();
            if (!disabled)
            {
                const std::lock_guard<std::mutex> lock(subNodesLock);
                this->processFrame();
                lock.~lock_guard();
            }
            else
            {
                DEBUG_LOG("pipeline on thread " << localThread->get_id() << " is shorting its output");
                cv::UMat data = previous->getOutput();
                outputLock.lock();
                output = data;
                outputLock.unlock();
            }
            localES->tickUpdate();
            end = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(std::chrono::milliseconds((1000 / this->fpsLimit) - std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()));
            changed = true;
        }
        ranOnce = true;
    }
    catch(cv::Exception e){
        std::cout << "\033[1;31m exception caught: " << e.what() << "\033[0m" << std::endl;
    }
    catch(exception e)
    {
        std::cout << "\033[1;31m caught exception: " << e.what() <<  "\033[0m" << std::endl;
        exit(1);
    }
    catch (...)
    {
        std::cout << "\033[1;31m caught unkown exception, possible memory corruption (pipelineNode)  \033[0m" << std::endl;
        exit(1);
    }
}