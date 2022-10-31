set(zbar_source_files
    zbar.cpp
    zbar.hpp
)
MESSAGE(STATUS "building zbar")
SET("OpenCV_DIR" "/usr/local/lib/")

find_package( OpenCV REQUIRED )

MESSAGE(STATUS "OpenCV_INCLUDE_DIRS : ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "Opencv_LINK_DIRS : ${Opencv_LINK_DIRS}")

add_library(zbarLib ${zbar_source_files})

find_package(PkgConfig REQUIRED)
pkg_check_modules(ZBar REQUIRED IMPORTED_TARGET zbar)

target_link_libraries(zbarLib ${OpenCV_LIBS})
target_link_libraries(zbarLib PkgConfig::ZBar)

MESSAGE(STATUS "Done building zbar")