mkdir build
cd build

cmake ..
cmake --build .

cd build/
./graph-repr ../resources/graph.txt