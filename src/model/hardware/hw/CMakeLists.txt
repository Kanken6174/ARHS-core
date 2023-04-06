set(hw_source_files
    inputManager.cpp
    inputManager.hpp
    inputKeys.hpp
)
MESSAGE(STATUS "building hw")
add_library(hw ${hw_source_files})

target_link_libraries(hw hw_ext)
target_link_libraries(hw threadweaver)
target_link_libraries(hw observers)

MESSAGE(STATUS "Done building hw")