FROM debian:latest
#update repo lists
RUN apt-get update -y

#install build essentials
RUN apt install -y cmake g++ wget unzip ccache

#install dependencies
RUN apt-get install -y unzip libgtk-3-dev libtbb-dev ffmpeg 

#install gstreamer
RUN apt-get install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio

#install hidapi
RUN apt-get install -y libhidapi-dev

#install opencv from source
WORKDIR /root
RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
RUN wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip
RUN unzip opencv.zip
RUN unzip opencv_contrib.zip
RUN mkdir -p build && cd build
RUN cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.x/modules ../opencv-4.x -D BUILD_opencv_java=OFF -D BUILD_opencv_python2=OFF -D BUILD_opencv_python3=OFF -D WITH_OPENGL=ON -D WITH_GTK=ON
RUN cmake --build . -j4
RUN make install

#build project
COPY ./../Sources/src/Visnode/ /usr/src/Visnode/
WORKDIR /usr/src/Visnode

RUN ./compile.sh