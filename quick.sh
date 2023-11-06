mkdir build
cd build

cmake ..
cmake --build .

cd build/
./graph-repr ../examples/graph.txt