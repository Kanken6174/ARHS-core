#ifndef _SERIAL_I
#define _SERIAL_I
// C library headers
#include <stdio.h>
#include <string.h>

#include <thread>
#include <vector>

#include <CppLinuxSerial/SerialPort.hpp>

#include "./../../../threadweaver/threadweaver.hpp"
#include "../../patterns/observer/observable.hpp"


class SerialPortManager : public MapObservable
{
public:
    SerialPortManager();
    void runPort();
    ~SerialPortManager(){
        serialPort->Close();
        delete serialPort;
    }
protected:
    bool shouldRun;
    mn::CppLinuxSerial::SerialPort* serialPort;
};
#endif