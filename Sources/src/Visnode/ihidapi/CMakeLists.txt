set(ihidapi_source_files
    hidapi_functions.cpp
    _hidapi.hpp
)
MESSAGE(STATUS "Building ihidapi")
add_library(ihiadpi ${ihidapi_source_files})

find_package(hidapi REQUIRED)

target_link_libraries(ihiadpi hidapi::hidapi)

MESSAGE(STATUS "Done building ihidapi")