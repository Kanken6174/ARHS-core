set(commands_src
    ./commands.hpp)
    
MESSAGE(STATUS "building commands")

add_library(commands ${commands_src})
set_target_properties(commands PROPERTIES LINKER_LANGUAGE CXX)

MESSAGE(STATUS "Done building commands")