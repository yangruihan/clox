#!/usr/bin/env bash

if [ ! -d "build/CMake/Release" ]; then
    mkdir -p build/CMake/Release
fi

if [ ! -d "bin/Release" ]; then
    mkdir -p bin/Release
fi

if [ ! -d "bin/Test" ]; then
    mkdir -p bin/Test
fi

if [ "$1" = "-d" ]; then
    cd build/CMake/Release && cmake -DCMAKE_BUILD_TYPE=Release -DDEBUG=ON -DDEBUG_TRACE_EXECUTION=OFF -DDEBUG_PRINT_CODE=OFF ../../../ && make -j
else
    cd build/CMake/Release && cmake -DCMAKE_BUILD_TYPE=Release -DDEBUG=OFF -DDEBUG_TRACE_EXECUTION=OFF -DDEBUG_PRINT_CODE=OFF ../../../ && make -j
fi
