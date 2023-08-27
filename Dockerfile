from ubuntu:latest

# install dependencies (lcov, cmake, gcc, g++, libgtk-3-dev, libwebkit2gtk-4.0-dev)
RUN apt-get update && apt-get install -y \
lcov \
cmake \
gcc \
g++ \
libgtk-3-dev \
libwebkit2gtk-4.0-dev

RUN apt-get install -y npm

RUN apt-get install -y \
curl \
zip \
unzip \
tar \
ninja-build



# copy the source code
COPY . /usr/src/app

# enter the source code directory
WORKDIR /usr/src/app

# Set environment variables
ENV CMAKE_C_COMPILER /usr/bin/gcc 
ENV CMAKE_CXX_COMPILER /usr/bin/g++

RUN cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCODE_COVERAGE=ON -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -G "Unix Makefiles"

RUN cmake --build build --Config Debug

RUN ctest --test-dir build --output-on-failure

RUN cmake --build build --target coverage