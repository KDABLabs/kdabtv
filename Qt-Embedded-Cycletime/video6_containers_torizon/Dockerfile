# take SDK container as base
FROM torizon/debian-cross-toolchain-arm64:4.0-bookworm-rc AS build

# install all required development packages
RUN apt-get update 
RUN apt-get install unzip
RUN apt-get install qtdeclarative5-dev:arm64 -y
RUN apt-get install build-essential -y
RUN apt-get install cmake -y

# get code you need to build
ADD poc.zip /home/torizon/
RUN unzip /home/torizon/poc.zip -d /home/torizon
RUN ls

# build code
RUN file /usr/lib/aarch64-linux-gnu/libQt5Quick.so.5.15.2 2>/dev/null
RUN cd /home/torizon/poc && cmake -DCMAKE_TOOLCHAIN_FILE=aarch64-toolchain.cmake -DCMAKE_PREFIX_PATH=/usr/lib/aarch64-linux-gnu/cmake/Qt5/ .
RUN cd /home/torizon/poc && ls
RUN cd /home/torizon/poc && make -j3

# create 2nd container for target
FROM --platform=linux/arm64 torizon/qt5-wayland-vivante:3 AS chsterz-qt5demo-torizon

# install runtime libraries
RUN apt-get update 
RUN apt-get install qml-module-qtquick-virtualkeyboard -y
RUN apt-get install qml-module-qtquick-controls2 -y
RUN apt-get install qml-module-qtcharts -y

# take application executable from build container
COPY --from=build /home/torizon/poc/poc /home/torizon/poc

# configure container to run your application at startup
ENV QT_IM_MODULE=qtvirtualkeyboard
ENV WAYLAND_DISPLAY=wayland-0
ENV XDG_RUNTIME_DIR=/tmp/1000-runtime-dir

CMD env /home/torizon/poc
