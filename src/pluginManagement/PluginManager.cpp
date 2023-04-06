#include "PluginManager.hpp"
#include "../pipeline/pipeline.hpp"
#include "../model/hardware/hw/extendables/DeviceTree.hpp"
#include <iostream>

PluginManager::PluginManager(Pipeline& pi){
        // Path to the folder
    fs::path folder_path = "./plugins";

    // Check if the folder exists
    if (fs::exists(folder_path) && fs::is_directory(folder_path)) {
        std::cout << "Folder exists\n";

        // Iterate over the files in the folder
        for (const auto& file : fs::directory_iterator(folder_path)) {
            // Check if the file is a regular file and a dynamic shared object file
            if (fs::is_regular_file(file.path()) && file.path().filename().string().substr(file.path().filename().string().size() - 3) == ".so") {
                std::cout << "Found a valid plugin at: " << file.path() << std::endl;
                Plugin* pl = new Plugin(file);
                std::cout << "Loaded plugin " << pl->identifier << " with manifest: " << pl->manifest << std::endl;
                if(pl->manifest == "") delete pl;
                else
                {
                    this->plugins[pl->identifier] = pl;
                    if(pl->loadNode != NULL){
                        std::cout << "loading plugin node\n";
                        SubNode* sn = pl->loadNode();
                        sn->enabled = false;
                        pi.getNodes().at(6)->addSubNode(sn);
                        std::cout << "loaded plugin node\n";
                    }
                    if(pl->loadDevice != NULL){
                        std::cout << "loading plugin devices\n";
                        SerialDevice* sd = pl->loadDevice();
                        if(sd->getDeviceID() != ""){
                            std::cout << "added device " << sd->getDeviceName()  << " with id " << sd->getDeviceID() << std::endl;
                            DeviceTree::GetInstance()->addDevice(sd);
                        }
                    }
                    /*if(pl->loadCommands != NULL){
                        std::cout << "loading plugin commands\n";
                        std::vector<DeviceCommand*> comms = pl->loadCommands();
                        pl->commands = comms;
                        for(auto c : pl->commands){
                            if(pl->identifier == "refresh"){
                                
                            }
                        }
                    }*/
                }
            }
        }
        DeviceTree::GetInstance()->build();
        std::cout <<"finished importing plugins" << std::endl;
    }
    else {
        std::cout << "Folder does not exist\n";
    }
}