#ifndef _DEVICE_
#define _DEVICE_
#include "DeviceCommand.hpp"
#include <map>
class Device{
    protected:
        std::string _tagidentifier;
        std::string _displayName;
        std::map<std::string, DeviceCommand*>* _commands = new std::map<std::string, DeviceCommand*>();
    public:
        inline Device(const std::string& tagidentifier) : _tagidentifier(tagidentifier){}
        inline const std::string getDeviceID() const{return _tagidentifier;}
        inline const std::string getDeviceName() const{return _displayName;}
        inline const std::map<std::string, DeviceCommand*>* getCommands() const{return _commands;}
};
#endif