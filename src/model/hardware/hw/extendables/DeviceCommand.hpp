#include "../../../../model/patterns/commands/commands.hpp"
#include <string>
class DeviceCommand: Command{
  public:
    std::string descriptor = "unnamed Command?";
    std::string identifier = "";
    unsigned int millisDelayReapeated = 50; // minimum delay to be respected if the task is repetitive
    bool displayed = false; //will display the command in the device tree entry for the device
    virtual void Execute() const = 0;
};