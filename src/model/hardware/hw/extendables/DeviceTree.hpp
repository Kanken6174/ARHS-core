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
    std::map<std::string, SerialDevice*>* serialDevices;
    std::map<std::string, std::thread*> deviceThreads;

    DeviceTree() : serialDevices()
    {
        serialDevices = new std::map<std::string, SerialDevice*>();
    }
    ~DeviceTree() {
        delete serialDevices;
    }

public:

    DeviceTree(DeviceTree &other) = delete;

    void operator=(const DeviceTree &) = delete;

    void build();
    void run();
    void addDevice(SerialDevice* sd){(*serialDevices)[sd->getDeviceID()] = sd;}

    static void runDevice(SerialDevice* device);

    static DeviceTree *GetInstance();
};
//#endif