#!/bin/bash
mkdir -p ~/code/auto_installed/
cd ~/code/auto_installed/

sudo apt update -y
sudo apt upgrade -y
sudo apt install -y git cmake g++ wget unzip build-essential ccache pkg-config

#------------------------------------------------------------------------------------Hidapi
sudo apt install -y libudev-dev libusb-1.0-0-dev
mkdir hid
cd hid
git clone https://github.com/libusb/hidapi
cd hidapi

cmake .
cmake --build . -j7
sudo make install
sudo ldconfig
#-------------------------------------------------------------------------------------Opencv
cd ~/code/auto_installed/

sudo apt install -y libtbb-dev ffmpeg freeglut3 freeglut3-dev binutils-gold libglew-dev mesa-common-dev libglew1.5-dev libglm-dev

mkdir ocv
cd ocv

wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip
unzip opencv.zip
unzip opencv_contrib.zip

rm opencv.zip
rm opencv_contrib.zip

mkdir -p build && cd build
cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.x/modules ../opencv-4.x -DWITH_OPENGL=ON -DWITH_GTK=ON -DWITH_QT=OFF -DWITHTBB=ON

cmake --build . -j7
sudo make install
sudo ldconfig