cmake_minimum_required(VERSION 3.10)

set(flying_window_src
    ./Model.hpp
    ./Mesh.hpp
    ./Shader.hpp
    ./Camera.hpp
    ./FlyingWindow.hpp
    ./TextRenderer.hpp
)

MESSAGE(STATUS "Building gl")

set(FreeType_DIR "/path/to/freetype/install/dir")

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(FreeType REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
)

MESSAGE(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "OpenGL_INCLUDE_DIRS: ${OPENGL_INCLUDE_DIRS}")
MESSAGE(STATUS "GLUT_INCLUDE_DIRS: ${GLUT_INCLUDE_DIRS}")
MESSAGE(STATUS "FreeType_INCLUDE_DIRS: ${FREETYPE_INCLUDE_DIRS}")

add_library(ARHSGL ${flying_window_src})

target_link_libraries(ARHSGL ${OPENGL_LIBRARIES})
target_link_libraries(ARHSGL ${GLUT_INCLUDE_DIRS})
target_link_libraries(ARHSGL ${OpenCV_LIBS})
target_link_libraries(ARHSGL ${FREETYPE_LIBRARIES})

MESSAGE(STATUS "Done building gl")