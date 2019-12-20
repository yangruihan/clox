cmake_minimum_required(VERSION 3.1)

set(PROJ_NAME clox)

project(${PROJ_NAME})

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

option(DEBUG "Debug Version" on)

if(DEBUG)
    add_definitions(-DDEBUG)
endif(DEBUG)

if(DEBUG_TRACE_EXECUTION)
    add_definitions(-DDEBUG_TRACE_EXECUTION)
endif(DEBUG_TRACE_EXECUTION)

if(DEBUG_PRINT_CODE)
    add_definitions(-DDEBUG_PRINT_CODE)
endif(DEBUG_PRINT_CODE)

if (DEBUG_STRESS_GC)
    add_definitions(-DDEBUG_STRESS_GC)
endif(DEBUG_STRESS_GC)

if (DEBUG_LOG_GC)
    add_definitions(-DDEBUG_LOG_GC)
endif(DEBUG_LOG_GC)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)

add_subdirectory(test)
