#include "Plugin.hpp"
#include <dlfcn.h>

Plugin::Plugin(fs::directory_entry sharedLibraryToLoad){
    libHandle = dlopen(sharedLibraryToLoad.path().string().c_str(), RTLD_LAZY);
    if(!libHandle) return;

    typedef std::string (*GetManifestFunc)();
    typedef std::string (*GetIdentifierFunc)();
    typedef SerialDevice* (*GenerateDeviceFunc)();
    typedef SubNode* (*GenerateSubnodeFunc)();
    typedef std::vector<DeviceCommand*> (*GenerateDeviceCommandsFunc)();

    GetManifestFunc getManifestFunc = (GetManifestFunc)dlsym(libHandle, "getManifest");
    GetIdentifierFunc getIdentifierFunc = (GetIdentifierFunc)dlsym(libHandle, "getidentifier");

    if(getManifestFunc != NULL)
        manifest = getManifestFunc();
    if(getIdentifierFunc != NULL)
        identifier = getIdentifierFunc();

    loadDevice = (GenerateDeviceFunc)dlsym(libHandle, "generateDevice");
    loadNode = (GenerateSubnodeFunc)dlsym(libHandle, "generateSubnode");
    loadCommands = (GenerateDeviceCommandsFunc)dlsym(libHandle, "generateDeviceCommands");
}

Plugin::~Plugin(){
    dlclose(libHandle);
}