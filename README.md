# Build
rm -rf build && mkdir build                                 
cd build
cmake ..
make && make install
cd ..

# Run
./build/os string
