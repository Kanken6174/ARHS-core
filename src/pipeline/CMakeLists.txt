set(pipeline_src
    ./abstract/pipelineNode.cpp
    ./abstract/pipelineNode.hpp
    ./members/cameraPickerNode.cpp
    ./members/cameraPickerNode.hpp
    ./members/displayOutputNode.cpp
    ./members/displayOutputNode.hpp
    ./members/uiDrawerNode.cpp
    ./members/uiDrawerNode.hpp
    ./members/uiMergerNode.cpp
    ./members/uiMergerNode.hpp
    ./members/zbarAnalysisNode.cpp
    ./members/zbarAnalysisNode.hpp
    ./members/videoCaptureNode.cpp
    ./members/videoCaptureNode.hpp
    ./members/pluginNode.cpp
    ./members/pluginNode.hpp

    ./members/subNodes/subNodes.hpp
    ./members/subNodes/fpsCounter.cpp
    ./members/subNodes/staticImageOverlayer.cpp
    ./members/subNodes/zbarOverlayer.cpp
    ./members/subNodes/uiMenus.hpp
    ./members/subNodes/uiMenuItem.cpp

    ./pipeline.cpp
    ./pipeline.hpp)
MESSAGE(STATUS "building pipeline")
SET("OpenCV_DIR" "/usr/local/lib/")

find_package( OpenCV REQUIRED )
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )


MESSAGE(STATUS "OpenCV_INCLUDE_DIRS : ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "Opencv_LINK_DIRS : ${Opencv_LINK_DIRS}")

add_library(pipelineLib ${pipeline_src})

target_link_libraries(pipelineLib windows)
target_link_libraries(pipelineLib ${OPENGL_LIBRARIES})
target_link_libraries(pipelineLib ${GLUT_INCLUDE_DIRS})
target_link_libraries(pipelineLib ${OpenCV_LIBS})
target_link_libraries(pipelineLib support)
target_link_libraries(pipelineLib psvr)
target_link_libraries(pipelineLib controllers)
target_link_libraries(pipelineLib hw)
target_link_libraries(pipelineLib threadweaver)
target_link_libraries(pipelineLib zbarLib)
target_link_libraries(pipelineLib PluginManager)
#target_link_libraries(pipelineLib observers)

MESSAGE(STATUS "Done building pipeline")