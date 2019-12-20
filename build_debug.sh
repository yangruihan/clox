#!/usr/bin/env bash

if [ ! -d "build/CMake/Debug" ]; then
    mkdir -p build/CMake/Debug
fi

if [ ! -d "bin/Debug" ]; then
    mkdir -p bin/Debug
fi

if [ ! -d "bin/Test" ]; then
    mkdir -p bin/Test
fi

cd build/CMake/Debug && cmake -DCMAKE_BUILD_TYPE=Debug -DDEBUG=ON -DDEBUG_TRACE_EXECUTION=ON -DDEBUG_PRINT_CODE=ON -DDEBUG_STRESS_GC=ON -DDEBUG_LOG_GC=ON ../../../ && make -j
