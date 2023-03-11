#include "./DeviceTree.hpp"

DeviceTree* DeviceTree::GetInstance(const std::string& value)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new DeviceTree();
    }
    return pinstance_;
}
