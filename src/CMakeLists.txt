cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Ofast -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -fPIC")
set(OpenGL_GL_PREFERENCE GLVND)

project(visnode)

#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../bin)
#set(CMAKE_BINARY_DIR /home/kanken/code/AHRS_core/Sources/src/Visnode)
find_package(OpenCV REQUIRED)
find_package(TBB REQUIRED)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-fsanitize=undefined,address")
#SET(GCC_COVERAGE_LINK_FLAGS    "-fsanitize=undefined,address")

#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#SET("OpenCV_DIR" "/usr/local/lib/")
include_directories(${OpenCV_INCLUDE_DIRS} )
link_directories(${CMAKE_BINARY_DIR})
MESSAGE(STATUS "OpenCV_INCLUDE_DIRS : ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "Opencv_LINK_DIRS : ${Opencv_LINK_DIRS}")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(threadweaver)
add_subdirectory(model/perfcheckers)
add_subdirectory(model/hardware/ihidapi)
add_subdirectory(model/hardware/cameras)
add_subdirectory(model/hardware/psvr)
add_subdirectory(model/hardware/hw/extendables)
add_subdirectory(model/hardware/hw)
add_subdirectory(model/controllers)
add_subdirectory(model/patterns/observer)
add_subdirectory(model/patterns/commands)
add_subdirectory(processing/zbar)
add_subdirectory(model/windows)
add_subdirectory(ui/support)
add_subdirectory(pipeline)
add_subdirectory(pluginManagement)
add_subdirectory(graphics)

set(main_source_files main.cpp main.hpp topLevelManager.cpp)

add_executable(prog ${main_source_files})

MESSAGE(STATUS "CMAKE FLAGS : ${LINK_OPTIONS}")

target_link_libraries(prog pipelineLib tbb Threads::Threads)

SET(GCC_COVERAGE_COMPILE_FLAGS "-L/usr/local/lib")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
