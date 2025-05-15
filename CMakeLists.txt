cmake_minimum_required(VERSION 3.10)
project(phys)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/
  ${PROJECT_SOURCE_DIR}/include/Dependencies/
  ${PROJECT_SOURCE_DIR}/include/Dependencies/PS/include/
  ${PROJECT_SOURCE_DIR}/include/Dependencies/PS/include/math/
  ${PROJECT_SOURCE_DIR}/include/Dependencies/SDL3/
)
set(LIBS_DIR ${PROJECT_SOURCE_DIR}/libs/SDL3/libSDL3.dll.a)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCE_FILE "${SRC_DIR}/*.cpp"
  "${PROJECT_SOURCE_DIR}/include/Dependencies/PS/src/math/*.cpp"
  "${PROJECT_SOURCE_DIR}/include/Dependencies/PS/src/*.cpp"
)
add_executable(phys ${SOURCE_FILE})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS_DIR})
