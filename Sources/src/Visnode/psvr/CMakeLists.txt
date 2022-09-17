set(psvr_source_files
    psvr.cpp
    _psvr.hpp
)
MESSAGE(STATUS "building psvr")
add_library(psvr ${psvr_source_files})

target_link_libraries(psvr ihidapi)

MESSAGE(STATUS "Done building psvr")