#include "../../../../model/patterns/commands/commands.hpp"
#include <string>
class DeviceCommand: Command{
  public:
    std::string descriptor = "unnamed Command?";
    bool displayed = false; //will display the command in the device tree entry for the device
    virtual void Execute() const = 0;
};