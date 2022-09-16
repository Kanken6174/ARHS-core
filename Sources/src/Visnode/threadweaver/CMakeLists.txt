set(thredweaver_source_files
    threadweaver.cpp
    threadweaver.hpp
)
MESSAGE(STATUS "building threadweaver")
add_library(threadweaver ${thredweaver_source_files})
MESSAGE(STATUS "done building threadweaver")