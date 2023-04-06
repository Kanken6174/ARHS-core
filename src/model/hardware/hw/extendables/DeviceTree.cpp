#include "./DeviceTree.hpp"
#include <filesystem>
#include <thread>
namespace fs = std::filesystem;

std::mutex DeviceTree::mutex_;
DeviceTree * DeviceTree::pinstance_;

DeviceTree* DeviceTree::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new DeviceTree();
    }
    return pinstance_;
}

void DeviceTree::build(){
    fs::path sys_path = "/sys/class/tty";

    // Check if the folder exists
    if (fs::exists(sys_path)) {
        std::cout << "device Folder exists\n";

        // Iterate over the devices in the folder
        for (const auto& file : fs::directory_iterator(sys_path)) {
            // Check if the file is a regular file and a dynamic shared object file
            std::string fileStr = file.path().filename().string();
            bool assigned = false;
            if (fileStr.find("USB") != std::string::npos || fileStr.find("ACM") != std::string::npos) {
                std::cout << "Found a valid device at: " << file.path() << std::endl;
                mn::CppLinuxSerial::SerialPort* serialPort = new mn::CppLinuxSerial::SerialPort("/dev/ttyACM0", 
                mn::CppLinuxSerial::BaudRate::B_460800, 
                mn::CppLinuxSerial::NumDataBits::EIGHT, 
                mn::CppLinuxSerial::Parity::NONE, 
                mn::CppLinuxSerial::NumStopBits::ONE);

                serialPort->SetTimeout(150); // Block for up to 100ms to receive data
                serialPort->Open();
                serialPort->Write("$");  //identify command
                std::string back;
                serialPort->Read(back);

                for(const auto& kv : *serialDevices){
                    if(back != "")
                        std::cout << "device sent back : " << back << std::endl;
                    if(back.find(kv.first) != std::string::npos){
                        std::cout << "uids matched! port assigned"<< std::endl;
                        (*serialDevices)[kv.first]->serialPort = serialPort;
                        (*serialDevices)[kv.first]->enabled = true;
                        assigned = true;
                        std::cout << "assign done"<< std::endl;
                    }else{
                        std::cout << "device sent back uid but no match, an extension may be missing"<< std::endl;
                        assigned = false;
                    }
                }

                if(!assigned){
                    serialPort->Close();
                    delete serialPort;
                    std::cout << "deleted " << fileStr << std::endl;
                }
            }
        }
        run();
    }
}

void DeviceTree::run(){
    std::cout << "running device tree" << std::endl;
    for(const auto& kv : *serialDevices){
        deviceThreads[kv.first] = new std::thread(&DeviceTree::runDevice, kv.second);
    }
    std::cout << "device tree running" << std::endl;
}

void DeviceTree::runDevice(SerialDevice* device){
    while(device->enabled){
        if(!device->working){
            device->working = true;
            device->runPort();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(device->workDelayMs));
    }
}