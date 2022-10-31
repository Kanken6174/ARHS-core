set(observers_src
    ./observable.cpp
    ./observable.hpp
    ./observer.hpp)
    
MESSAGE(STATUS "building observers")
SET("OpenCV_DIR" "/usr/local/lib/")

MESSAGE(STATUS "OpenCV_INCLUDE_DIRS : ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "Opencv_LINK_DIRS : ${Opencv_LINK_DIRS}")

add_library(observers ${observers_src})

MESSAGE(STATUS "Done building observers")