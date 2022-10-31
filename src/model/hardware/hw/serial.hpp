// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <errno.h>   // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

#include <thread>
#include <vector>

#include "./../../../threadweaver/threadweaver.hpp"
#include "../../patterns/observer/observable.hpp"

class SerialPortManager : public Observable
{
public:
    SerialPortManager();
    void runPort();

private:
    bool shouldRun;
    int serialPort;
};