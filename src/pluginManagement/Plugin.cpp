#include "Plugin.hpp"
#include <dlfcn.h>

Plugin::Plugin(fs::directory_entry sharedLibraryToLoad){
    void* libHandle = dlopen(sharedLibraryToLoad.path().string().c_str(), RTLD_LAZY);
    if(!libHandle) return;
}