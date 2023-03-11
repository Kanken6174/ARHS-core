#include "./serial.hpp"
#include <CppLinuxSerial/SerialPort.hpp>
#include <string>

SerialPortManager::SerialPortManager()
{
    std::cout << "opening serial port /dev/ttyUSB0" << std::endl;
    serialPort = new mn::CppLinuxSerial::SerialPort("/dev/ttyUSB0", 
    mn::CppLinuxSerial::BaudRate::B_9600, 
    mn::CppLinuxSerial::NumDataBits::EIGHT, 
    mn::CppLinuxSerial::Parity::NONE, 
    mn::CppLinuxSerial::NumStopBits::ONE);
    std::cout << "done" << std::endl;

    if (serialPort->GetState() == mn::CppLinuxSerial::State::CLOSED)
    {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return;
    }

    shouldRun = false;
    std::cout << "starting hardware watcher thread" << std::endl;
    std::thread *t = new std::thread(&SerialPortManager::runPort, this);
    std::cout << "done" << std::endl;
    Threadweaver::stick_this_thread_to_core(t, CAMCORE);
    //Threadweaver::hardwareWatcherThread = t;
    shouldRun = true;
}

void SerialPortManager::runPort()
{
    while (!shouldRun)
    {
    }
    char read_buf[256];
    int n = 0;
    while (shouldRun)
    {
        std::string dat;
        serialPort->Read(dat);
        if (dat != "")
        {
            sendMessage("",dat);
            /*
            switch (c)
            {
            case 'U':
                cout << c << "++" << endl;
                ui::UiController::selectedUp();
                break;
            case 'D':
                cout << c << "--" << endl;
                ui::UiController::selectedDown();
                break;
            case '1':
                ui::UiController::click();
                break;
            case '2':
                ui::UiController::click();
                break;
            case '3':
                ui::UiController::click();
                break;
            case '4':
                ui::UiController::click();
                break;
            default:
                break;
            }
            */
        }
        std::fill_n(read_buf, n, 0);
    }
}