#ifndef _SERIAL_DEVICE_
#define _SERIAL_DEVICE_

#include "./Device.hpp"
#include "../serial.hpp"

#include <stdio.h>
#include <string.h>

#include <thread>
#include <vector>
#include <iostream>

#include <iterator>
#include <algorithm>

class IdentifiyCommand;

class SerialDevice : public Device{
    protected:
        std::string _serialPort;
        unsigned int _baudrate;
        std::string lastData;
    public:
        mn::CppLinuxSerial::SerialPort serialPort;
        DeviceCommand* ic;
        SerialDevice(const std::string& serialPort) : Device("blank"), _serialPort(serialPort){}
        void getID();
        ~SerialDevice(){
            delete ic;
        }
};

class IdentifiyCommand : public DeviceCommand{
    private:
        SerialDevice* _sd;
    public:
        IdentifiyCommand(SerialDevice* sd) : _sd(sd){}

        void Execute() const override { 
            if(_sd->serialPort.GetState() != mn::CppLinuxSerial::State::OPEN)
                return;
            _sd->serialPort.Write("$");
            std::string readData;
            _sd->serialPort.Read(readData);
        }
};
#endif