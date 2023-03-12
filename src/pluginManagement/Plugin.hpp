#include <string>
#include <filesystem>
#include <vector>
#include "../model/hardware/hw/extendables/SerialDevice.hpp"
namespace fs = std::filesystem;

class SubNode;

class Plugin{
    protected:
        fs::directory_entry pluginFile;
        void* libHandle;
    public:
        std::vector<DeviceCommand*> commands;
        std::string manifest = "";
        std::string identifier = "";

        Plugin(fs::directory_entry sharedLibraryToLoad);
        ~Plugin();
        std::function<SerialDevice*()> loadDevice = NULL;
        std::function<SubNode*()> loadNode = NULL;
        std::function<std::vector<DeviceCommand*>()> loadCommands = NULL;
};