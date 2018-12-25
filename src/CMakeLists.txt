aux_source_directory(. SRC_FILES)

file(GLOB HEADERS_PLUS1 "*.hpp")
file(GLOB HEADERS1      "*.h")
file(GLOB HEADERS_PLUS2 "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB HEADERS2      "${PROJECT_SOURCE_DIR}/include/*.h")

source_group("Headers" FILES ${HEADERS_PLUS1})
source_group("Headers" FILES ${HEADERS1})
source_group("Headers" FILES ${HEADERS_PLUS2})
source_group("Headers" FILES ${HEADERS2})

# set output path
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/Debug")
else(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/Release")
endif(CMAKE_BUILD_TYPE MATCHES "Debug")

add_executable(
    ${PROJ_NAME}
    ${SRC_FILES}
    ${HEADERS_PLUS1}
    ${HEADERS_PLUS2}
    ${HEADERS1}
    ${HEADERS2}
)

target_link_libraries(
    ${PROJ_NAME}
)
