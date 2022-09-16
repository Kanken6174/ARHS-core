set(ui_source_files
    ./uiElements/uiElements.cpp
    ./uiElements/uiElements.hpp
    ui.cpp
    uiController.cpp
    uiDrawer.cpp
    uiManager.cpp
    _ui.hpp
)
MESSAGE(STATUS "building ui")
SET("OpenCV_DIR" "/usr/local/lib/")

find_package( OpenCV REQUIRED )


add_library(ui ${ui_source_files})

target_link_libraries(ui Opencv)
MESSAGE(STATUS "Done building ui")