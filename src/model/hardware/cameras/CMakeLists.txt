set(cameras_source_files
    camEnum.cpp
    cameraManager.cpp
    _cam.hpp
)
MESSAGE(STATUS "building cameras")
add_library(cameras ${cameras_source_files})

MESSAGE(STATUS "OpenCV_INCLUDE_DIRS : ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "Opencv_LINK_DIRS : ${Opencv_LINK_DIRS}")

#SET("OpenCV_DIR" "/usr/local/lib/")

find_package( OpenCV REQUIRED )

target_link_libraries(cameras ${OpenCV_LIBS})
target_link_libraries(cameras threadweaver)
MESSAGE(STATUS "Done building cameras")