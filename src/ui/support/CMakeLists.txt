set(ui_source_files
    ./UiSupport.cpp
    ./UiSupport.hpp)
MESSAGE(STATUS "building ui")
SET("OpenCV_DIR" "/usr/local/lib/")

find_package( OpenCV REQUIRED )
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )


MESSAGE(STATUS "OpenCV_INCLUDE_DIRS : ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "Opencv_LINK_DIRS : ${Opencv_LINK_DIRS}")

add_library(support ${ui_source_files})

target_link_libraries(support ${OPENGL_LIBRARIES})
target_link_libraries(support ${OpenCV_LIBS})

MESSAGE(STATUS "Done building ui")