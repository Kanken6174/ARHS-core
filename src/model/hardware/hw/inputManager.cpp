#include "./inputManager.hpp"
#include <CppLinuxSerial/SerialPort.hpp>
#include <string>
#include <mutex>

std::mutex InputManager::mutex_;
InputManager * InputManager::pinstance_;

InputManager::InputManager()
{
    std::cout << "InputManager is now online" << std::endl;
}

void InputManager::sendinput(unsigned int input, InputTypes type){
    sendMessage(std::to_string((unsigned int)type),std::to_string(input));
}

InputManager* InputManager::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new InputManager();
    }
    return pinstance_;
}