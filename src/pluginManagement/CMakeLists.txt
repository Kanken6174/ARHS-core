set(pluginManager_src
    ./PluginManager.hpp
    ./PluginManager.cpp
    ./Plugin.hpp
    ./Plugin.cpp)
    
MESSAGE(STATUS "building PluginManager")

add_library(PluginManager ${pluginManager_src})
set_target_properties(PluginManager PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(PluginManager pipelineLib)

MESSAGE(STATUS "Done building PluginManager")