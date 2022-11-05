set(controllers_source_files
    ./ui/uiController.cpp
    ./ui/uiController.cpp
    ./ui/menuItem.hpp
    ./ui/menu.hpp
    ./ui/menu.cpp
)
MESSAGE(STATUS "building controllers")
add_library(controllers ${controllers_source_files})

MESSAGE(STATUS "OpenCV_INCLUDE_DIRS : ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "Opencv_LINK_DIRS : ${Opencv_LINK_DIRS}")

#SET("OpenCV_DIR" "/usr/local/lib/")

find_package( OpenCV REQUIRED )
find_package( OpenGL REQUIRED )

target_link_libraries(controllers ${OpenCV_LIBS})
target_link_libraries(controllers ${OPENGL_LIBRARIES})
target_link_libraries(controllers cameras)
target_link_libraries(controllers hw)
target_link_libraries(controllers psvr)
MESSAGE(STATUS "Done building controllers")