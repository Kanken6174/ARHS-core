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

#include "../../patterns/observer/observable.hpp"
#include "../../patterns/observer/observer.hpp"
#include "../../threadweaver/threadweaver.hpp"

class SerialPortManager : Observable
{
public:
    SerialPortManager();
    void runPort();

private:
    bool shouldRun;
    int serialPort;
};