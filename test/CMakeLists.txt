aux_source_directory(. SRC_FILES)

file(GLOB_RECURSE HEADERS_PLUS ./*.hpp)
file(GLOB_RECURSE HEADERS ./*.h)

source_group("Headers" FILES ${HEADERS_PLUS})
source_group("Headers" FILES ${HEADERS})

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/test")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/Test")

add_executable(
    ${PROJ_NAME}_test
    ${SRC_FILES}
    ${HEADERS_PLUS}
    ${HEADERS}
)

target_link_libraries(
    ${PROJ_NAME}_test
)
