#include "PluginManager.hpp"
#include "../pipeline/pipeline.hpp"
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
                Plugin* pl = new Plugin(file);
                if(pl->manifest == "") delete pl;
                else
                { 
                    this->plugins[pl->identifier] = pl;
                    if(pl->loadDevice != NULL){
                        SerialDevice* sd = pl->loadDevice();
                        //add to serial device manager
                    }
                    if(pl->loadNode != NULL){
                        pi.getNodes().at(PIPELINE_UI_DRAWER_NODE)->addSubNode(pl->loadNode());
                    }
                    if(pl->loadCommands != NULL){
                        std::vector<DeviceCommand*> comms = pl->loadCommands();
                        pl->commands = comms;
                        for(auto c : pl->commands){
                            if(pl->identifier == "refresh"){
                                
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        std::cout << "Folder does not exist\n";
    }
}