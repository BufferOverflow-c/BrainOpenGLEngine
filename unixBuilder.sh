#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_MAKE_PROGRAM=ninja -G Ninja  -DCMAKE_C_FLAGS="-Wno-unused-parameter" -DCMAKE_CXX_FLAGS="-Wno-deprecated-declarations" -B ./cmake-build-debug -S .
cd cmake-build-debug
ninja -j9 -k0 -v
cd ..
