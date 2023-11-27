# PathFinder
Integration of Qt and SFML in C++.

# For Linux
`sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
`
`cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build`

# For Windows 

`cmake -S . -B build
cmake --build build --config Release`
