#include "./serial.hpp"
#include <string>

SerialPortManager::SerialPortManager()
{
    struct termios tty;

    std::cout << "opening serial port /dev/ttyUSB0" << std::endl;
    serialPort = open("/dev/ttyUSB0", O_RDWR); // open serial port
    std::cout << "done" << std::endl;

    if (serialPort < 0)
    {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return;
    }

    if (tcgetattr(serialPort, &tty) != 0)
    { // read serial port configuration
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return;
    }

    // local flags
    tty.c_lflag &= ~ICANON; // enable canonical mode
    tty.c_lflag &= ~ECHO;   // Disable echo
    tty.c_lflag &= ~ECHOE;  // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG;   // Disable interpretation of INTR, QUIT and SUSP
    // input modes
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);                                      // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special handling of received bytes
    // output modes
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // c_cc
    tty.c_cc[VTIME] = 1; // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;
    // baudrate
    cfsetispeed(&tty, B9600); // set baudrate (input)
    cfsetospeed(&tty, B9600); // (output)

    // Save tty settings, also checking for error
    if (tcsetattr(serialPort, TCSANOW, &tty) != 0)
    {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
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
        n = read(serialPort, &read_buf, sizeof(read_buf));
        if (n > 0)
        {
            char c = read_buf[0];
            sendMessage("",std::string()+c);
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