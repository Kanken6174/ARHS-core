cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Ofast")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

project(visnode)

#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../bin)
#set(CMAKE_BINARY_DIR /home/kanken/code/AHRS_core/Sources/src/Visnode)
find_package(OpenCV REQUIRED)
find_package(TBB REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#SET("OpenCV_DIR" "/usr/local/lib/")
include_directories(${OpenCV_INCLUDE_DIRS} )
link_directories(${CMAKE_BINARY_DIR})
MESSAGE(STATUS "OpenCV_INCLUDE_DIRS : ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "Opencv_LINK_DIRS : ${Opencv_LINK_DIRS}")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(perfcheckers)
add_subdirectory(threadweaver)
add_subdirectory(ihidapi)
add_subdirectory(cameras)
add_subdirectory(psvr)
add_subdirectory(ui)
add_subdirectory(hw)

set(main_source_files main.cpp main.hpp)

add_executable(prog ${main_source_files})

MESSAGE(STATUS "CMAKE FLAGS : ${LINK_OPTIONS}")

target_link_libraries(prog hw tbb Threads::Threads)

SET(GCC_COVERAGE_COMPILE_FLAGS "-L/usr/local/lib")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
