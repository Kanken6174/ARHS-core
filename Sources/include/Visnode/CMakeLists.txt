cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)

project( visnode )

find_package(OpenCV REQUIRED)

SET("OpenCV_DIR" "/usr/local/lib/")
include_directories(${OpenCV_INCLUDE_DIRS} )
link_directories(${Opencv_LINK_DIRS})

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(threadweaver)
add_subdirectory(ihidapi)
add_subdirectory(cameras)
add_subdirectory(psvr)
add_subdirectory(ui)
add_subdirectory(hw)

set(main_source_files main.cpp main.hpp)

add_executable(prog ${main_source_files})

target_link_libraries(prog hw)


SET(GCC_COVERAGE_COMPILE_FLAGS "-L/usr/local/lib")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})