//#ifndef _DEVICETREE_
//#define _DEVICETREE_
#include <mutex>
#include <string>
#include <map>
#include "./SerialDevice.hpp"

class SerialDevice;

class DeviceTree    //a singleton
{
private:
    static DeviceTree * pinstance_;
    static std::mutex mutex_;

protected:
    std::map<__uint128_t, SerialDevice*>* serialDevices;

    DeviceTree() : serialDevices()
    {
        serialDevices = new std::map<__uint128_t, SerialDevice*>();
    }
    ~DeviceTree() {
        delete serialDevices;
    }

public:

    DeviceTree(DeviceTree &other) = delete;

    void operator=(const DeviceTree &) = delete;

    static DeviceTree *GetInstance(const std::string& value);
};
//#endif