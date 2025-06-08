cmake_minimum_required(VERSION 3.16)
project(phys LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Binary dir: ${PROJECT_BINARY_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

set(IMGUI_DIR "${PROJECT_SOURCE_DIR}/include/Dependencies/imgui")

set(INCLUDE_DIRS
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/Dependencies"
    "${PROJECT_SOURCE_DIR}/include/Dependencies/PS/include"
    "${PROJECT_SOURCE_DIR}/include/Dependencies/PS/include/math"
    "${PROJECT_SOURCE_DIR}/include/Dependencies/PS/include/collision"
    "${PROJECT_SOURCE_DIR}/include/Dependencies/PS/include/dynamics"
    "${PROJECT_SOURCE_DIR}/include/Dependencies/PS/include/other"
    "${PROJECT_SOURCE_DIR}/include/Dependencies/SDL3"
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
)
set(SDL3_LIB "${PROJECT_SOURCE_DIR}/libs/SDL3/libSDL3.dll.a")

file(GLOB_RECURSE SOURCE_FILES
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/scenes/*.cpp"
    "${PROJECT_SOURCE_DIR}/include/Dependencies/PS/src/math/*.cpp"
    "${PROJECT_SOURCE_DIR}/include/Dependencies/PS/src/collision/*.cpp"
    "${PROJECT_SOURCE_DIR}/include/Dependencies/PS/src/dynamics/*.cpp"
    "${PROJECT_SOURCE_DIR}/include/Dependencies/PS/src/*.cpp"
    "${IMGUI_DIR}/*.cpp"
    "${IMGUI_DIR}/backends/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_LIB})
