set(ext_source_files
    Device.hpp
    DeviceCommand.hpp
    DeviceTree.cpp
    DeviceTree.hpp
    SerialDevice.hpp
)
MESSAGE(STATUS "building hw_ext")
add_library(hw_ext ${ext_source_files})
target_link_libraries(hw_ext CppLinuxSerial)
MESSAGE(STATUS "Done building hw_ext")