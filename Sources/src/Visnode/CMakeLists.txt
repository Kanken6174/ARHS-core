cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

project(visnode)

#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../bin)
set(CMAKE_BINARY_DIR /home/kanken/code/project-/Sources/src/Visnode/)
find_package(OpenCV REQUIRED)
find_package(TBB REQUIRED)


#SET("OpenCV_DIR" "/usr/local/lib/")
include_directories(${OpenCV_INCLUDE_DIRS} )
link_directories(${CMAKE_BINARY_DIR})
MESSAGE(STATUS "OpenCV_INCLUDE_DIRS : ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "Opencv_LINK_DIRS : ${Opencv_LINK_DIRS}")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(threadweaver)
add_subdirectory(ihidapi)
add_subdirectory(cameras)
add_subdirectory(psvr)
add_subdirectory(ui)
add_subdirectory(hw)

set(main_source_files main.cpp main.hpp)

add_executable(prog ${main_source_files})

MESSAGE(STATUS "CMAKE FLAGS : ${LINK_OPTIONS}")

target_link_libraries(prog hw tbb)

SET(GCC_COVERAGE_COMPILE_FLAGS "-L/usr/local/lib")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})