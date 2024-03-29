git clone https://github.com/Mezozoysky/soil/
cd soil
mkdir cmake-build
cmake -B cmake-build -S . -G "Unix Makefiles"
cd cmake-build
make all
sudo make install
cd ../..
rm -rf ./soil