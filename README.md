# Blackjack
This is a semester project for a c++ class I have!

To build:

# Windows: 
Run windows_dependencies.bat first, and then build through cmake.
```
cd [[project dir]]
mkdir build-cmake
cmake -B build-cmake -S . -G "Unix Makefiles"
cd build-cmake
make all
mv KMblackjack.exe ../src
cd ../src
./KMblackjack.exe
```

# Linux:
Install the following dependencies through your package manager:
glfw,opengl,glm,freetype,GLEW,cmake,make,gcc
run linux_soil.sh and then build through cmake
```
cd [[project dir]]
mkdir build-cmake
cmake -B build-cmake -S . -G "Unix Makefiles"
cd build-cmake
make all
mv KMblackjack ../src
cd ../src
./KMblackjack
```

Sorry Mac users. I don't own one, but you can probably adapt from the linux build