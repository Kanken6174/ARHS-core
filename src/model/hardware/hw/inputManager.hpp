#ifndef INPUT_MANAGER
#define INPUT_MANAGER
// C library headers
#include <stdio.h>
#include <string.h>

#include <thread>
#include <vector>
#include <mutex>

#include "./../../../threadweaver/threadweaver.hpp"
#include "../../patterns/observer/observable.hpp"
#include "inputKeys.hpp"


class InputManager : public MapObservable
{
public:
    InputManager();
    ~InputManager(){}
    void sendinput(unsigned int input, InputTypes type);
    static InputManager *GetInstance();
protected:
    static std::mutex mutex_;
    static InputManager * pinstance_;
};

#endif