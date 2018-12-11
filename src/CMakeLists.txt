aux_source_directory(. SRC_FILES)

file(GLOB HEADERS_PLUS "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")

source_group("Headers" FILES ${HEADERS_PLUS})
source_group("Headers" FILES ${HEADERS})

# set output path
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/Debug")
else(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/Release")
endif(CMAKE_BUILD_TYPE MATCHES "Debug")

add_executable(
    ${PROJ_NAME}
    ${SRC_FILES}
    ${HEADERS_PLUS}
    ${HEADERS}
)

target_link_libraries(
    ${PROJ_NAME}
)
