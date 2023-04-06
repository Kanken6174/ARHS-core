#ifndef _SERIAL_I
#define _SERIAL_I
// C library headers
#include <stdio.h>
#include <string.h>

#include <thread>
#include <vector>

#include "./../../../threadweaver/threadweaver.hpp"
#include "../../patterns/observer/observable.hpp"
#include "inputKeys.hpp"


class InputManager : public MapObservable
{
public:
    InputManager();
    ~InputManager(){}
    void sendinput(unsigned int input, InputTypes type);
protected:
    bool shouldRun;
};
#endif