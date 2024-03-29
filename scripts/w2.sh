git clone https://github.com/nigels-com/glew
cd glew/auto
make all
cd ../..
cd glew/build/cmake
mkdir build
cmake -B build -S . -G "Ninja" -DBUILD_SHARED_LIBS=OFF
cd build
cmake --build .
cmake --install . --config Debug
cd ../../../..
rm -rf ./glew
git clone https://github.com/g-truc/glm
cd glm
mkdir cmake-build
cmake -B cmake-build -S . -G "Unix Makefiles"
cd cmake-build
make all
make install
cd ../..
rm -rf ./glm
git clone https://github.com/freetype/freetype
cd freetype
mkdir cmake-build
cmake -B cmake-build -S . -G "Unix Makefiles"
cd cmake-build
make all
make install
cd ../..
rm -rf ./freetype
git clone https://github.com/Mezozoysky/soil/
cd soil
mkdir cmake-build
cmake -B cmake-build -S . -G "Unix Makefiles"
cd cmake-build
make all
make install
cd ../..
rm -rf ./soil
git clone https://github.com/glfw/glfw
cd glfw
cmake -B cmake-build -S . -G "Unix Makefiles"
cd cmake-build
make all
make install
cd ../..
rm -rf ./glfw