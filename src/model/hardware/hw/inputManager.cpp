#include "./inputManager.hpp"
#include <CppLinuxSerial/SerialPort.hpp>
#include <string>

InputManager::InputManager()
{
    std::cout << "InputManager is now online" << std::endl;
}

void InputManager::sendinput(unsigned int input, InputTypes type){
    sendMessage(std::to_string((unsigned int)type),std::to_string(input));
}