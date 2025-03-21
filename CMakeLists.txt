cmake_minimum_required(VERSION 3.10)
project(PhysicalSimulation)
set(INCLUDE_DIR ./include/GLAD/ 
                ./include/imgui/ 
                ./include/Graphics/ 
                ./include/)

include_directories(${INCLUDE_DIR})


file(GLOB_RECURSE SOURCE_FILE   ./src/*.cpp 
                                ./src/GLAD/glad.c 
                                ./src/imgui/*.cpp
                                ./src/Graphics/*.cpp)
message("正在编译")
add_executable(${PROJECT_NAME} ${SOURCE_FILE})
message("编译完成")

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

set(GLFW_LIB ${PROJECT_SOURCE_DIR}/libs/GLFW/lib-mingw-w64/libglfw3dll.a)

target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_LIB})
