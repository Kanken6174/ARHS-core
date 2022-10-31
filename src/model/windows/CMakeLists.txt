set(wind_source_files
    window.cpp
    window.hpp
    windowManager.cpp
    windowManager.hpp
)
MESSAGE(STATUS "Building windows")

find_package( OpenCV REQUIRED )
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_library(windows ${wind_source_files})

target_link_libraries(windows ${OPENGL_LIBRARIES})
target_link_libraries(windows ${OpenCV_LIBS})

MESSAGE(STATUS "Done building windows")