cmake_minimum_required(VERSION 3.10)

set(flying_window_src
    ./Model.h
    ./Mesh.h
    ./Shader.h
    ./Camera.h
    ./FlyingWindow.h
    ./TextRenderer.h
)

MESSAGE(STATUS "Building Graphics")

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(FreeType2 REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
)

MESSAGE(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "OpenGL_INCLUDE_DIRS: ${OPENGL_INCLUDE_DIRS}")
MESSAGE(STATUS "GLUT_INCLUDE_DIRS: ${GLUT_INCLUDE_DIRS}")
MESSAGE(STATUS "FreeType_INCLUDE_DIRS: ${FREETYPE_INCLUDE_DIRS}")

add_library(GFXLib ${flying_window_src})
set_target_properties(GFXLib PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(GFXLib ${OPENGL_LIBRARIES})
target_link_libraries(GFXLib ${GLUT_INCLUDE_DIRS})
target_link_libraries(GFXLib ${OpenCV_LIBS})
target_link_libraries(GFXLib ${FREETYPE_LIBRARIES})
target_link_libraries(GFXLib ${FREETYPE_LIBRARIES})
target_include_directories(GFXLib PRIVATE ${FREETYPE_INCLUDE_DIRS})

MESSAGE(STATUS "Done building Graphics")
