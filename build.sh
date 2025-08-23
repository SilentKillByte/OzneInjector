#!/bin/bash
set -e
rm -rf build pornomon
mkdir build
cd build
cmake -G Ninja -DCMAKE_CXX_COMPILER=clang++ ..
ninja
cd ..
rm -rf build
echo "Done"
echo "libs in pornomon/"
