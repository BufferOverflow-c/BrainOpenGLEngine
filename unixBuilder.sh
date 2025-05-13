#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_OSX_ARCHITECTURES=x86_64 -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -B ./cmake-build-debug -S . && cd cmake-build-debug && ninja -j 9
#make Shaders && ./Brain
./Brain
cd ..
rm -rf cmake-build-debug
