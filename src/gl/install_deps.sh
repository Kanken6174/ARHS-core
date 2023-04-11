#!/bin/bash

# Update package lists
sudo apt-get update

# Install necessary packages
sudo apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libopencv-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    freeglut3-dev \
    libfreetype6-dev

# Download and install GLFW
git clone https://github.com/glfw/glfw.git
cd glfw
mkdir build && cd build
cmake .. && make
sudo make install
cd ../..
rm -rf glfw

# Download and install GLAD
git clone https://github.com/Dav1dde/glad.git
cd glad
mkdir build && cd build
cmake .. && make
sudo make install
cd ../..
rm -rf glad

# Download and install GLEW
wget https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.tgz
tar -xvf glew-2.2.0.tgz
cd glew-2.2.0/build
cmake ./cmake && make
sudo make install
cd ../..
rm -rf glew-2.2.0
rm glew-2.2.0.tgz

echo "All dependencies have been installed."