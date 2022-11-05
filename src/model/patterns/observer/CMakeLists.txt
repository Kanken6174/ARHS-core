set(observers_src
    ./observable.cpp
    ./observable.hpp
    ./observer.hpp)
    
MESSAGE(STATUS "building observers")

add_library(observers ${observers_src})

MESSAGE(STATUS "Done building observers")