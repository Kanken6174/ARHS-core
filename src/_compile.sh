#!/bin/bash

VERSION=$(dpkg -s libhidapi-dev 2> /dev/null | grep "Version" | cut -d':' -f2)

HEADERS="./threadweaver/*.hpp ./cameras/_cam.hpp ./ihidapi/_hidapi.hpp ./psvr/_psvr.hpp ./ui/uiElements/uiElements.hpp ./ui/_ui.hpp ./hw/*.hpp ./main.hpp"
SOURCES="./threadweaver/*.cpp ./cameras/*.cpp ./ihidapi/*.cpp ./psvr/*.cpp ./ui/uiElements/*.cpp  ./ui/*.cpp ./hw/*.cpp  ./main.cpp"
LIBRARIES="-ltbb -l:libhidapi-hidraw.so.0 -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lopencv_videoio -std=c++17"

INCLUDE_PATHS="-I/usr/local/include/opencv4"
# LIBRARY_PATHS="-L/lib/x86_64-linux-gnu/ -L/usr/local/lib/"
LIBRARY_PATHS="-L/lib/aarch64-linux-gnu/ -L/usr/local/lib/"

if [[ -z $VERSION ]]
then
    echo "libhidapi is missing!!!"
    #sudo apt install libhidapi-dev
elif [[ $VERSION != " 0.11.2-1" ]]
then
    echo "|"$VERSION"|"
    echo "libhidapi is not the right version!!!"
    #sudo apt --only-upgrade install libhidapi-dev
else
    echo "libhidapi is installed"
fi

echo "compiling..."
g++ -Ofast -pg $SOURCES $HEADERS $INCLUDE_PATHS $LIBRARY_PATHS $LIBRARIES -o prog
echo "done compiling"
