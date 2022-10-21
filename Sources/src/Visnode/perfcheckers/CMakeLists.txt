set(perfcheckers_source_files
    framerate.cpp
    fcheckManager.cpp
    framerate.hpp
)
MESSAGE(STATUS "Building perfcheckers")
add_library(perfcheckers ${perfcheckers_source_files})

MESSAGE(STATUS "Done building perfcheckers")