set(thredweaver_source_files
    threadweaver.cpp
    threadweaver.hpp
    debugging.hpp
)
MESSAGE(STATUS "building threadweaver")
add_library(threadweaver ${thredweaver_source_files})
target_link_libraries(threadweaver perfcheckers)
MESSAGE(STATUS "done building threadweaver")