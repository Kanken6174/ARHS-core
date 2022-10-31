set(ui_source_files
    ./abstract/pipelineNode.cpp
    ./abstract/pipelineNode.hpp
    ./members/cameraPickerNode.cpp
    ./members/cameraPickerNode.hpp
    ./members/displayOutputNode.cpp
    ./members/displayOutputNode.hpp
    ./abstract/pipelineNode.cpp
    ./abstract/pipelineNode.hpp
    ./abstract/pipelineNode.cpp
    ./abstract/pipelineNode.hpp
MESSAGE(STATUS "building ui")
SET("OpenCV_DIR" "/usr/local/lib/")

find_package( OpenCV REQUIRED )
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )


MESSAGE(STATUS "OpenCV_INCLUDE_DIRS : ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "Opencv_LINK_DIRS : ${Opencv_LINK_DIRS}")

add_library(ui ${ui_source_files})

target_link_libraries(ui ${OPENGL_LIBRARIES})
#target_link_libraries(ui ${GLUT_INCLUDE_DIRS})
#target_link_libraries(ui ${OpenCV_LIBS})
#target_link_libraries(ui psvr)
#target_link_libraries(ui cameras)
#target_link_libraries(ui zbarLib)

MESSAGE(STATUS "Done building ui")