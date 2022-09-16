set(hw_source_files
    serial.cpp
    serial.hpp
)
MESSAGE(STATUS "building hw")
add_library(hw ${hw_source_files})

target_link_libraries(hw ui)
MESSAGE(STATUS "Done building hw")