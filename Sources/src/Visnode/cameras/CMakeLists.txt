set(cameras_source_files
    camEnum.cpp
    cameraManager.cpp
    _cam.hpp
)
MESSAGE(STATUS "building cameras")
add_library(cameras ${cameras_source_files})

#SET("OpenCV_DIR" "/usr/local/lib/")

find_package( OpenCV REQUIRED )

MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")

target_link_libraries(cameras OpenCV)
MESSAGE(STATUS "Done building cameras")