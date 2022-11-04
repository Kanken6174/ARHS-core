cmake_minimum_required(VERSION 3.1)
set(ihidapi_source_files
    hidapi_functions.cpp
    _hidapi.hpp
)
MESSAGE(STATUS "Building ihidapi")
add_library(ihidapi ${ihidapi_source_files})

find_package(hidapi REQUIRED)

target_link_libraries(ihidapi PRIVATE hidapi::hidapi)

MESSAGE(STATUS "Done building ihidapi")
