cmake_minimum_required(VERSION 3.16)
project(PhysicalSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(PhysicalSimulation/vendor/SDL3-cmake)
add_subdirectory(PhysicalSimulation/vendor/imgui-cmake)

add_subdirectory(PhysicalSimulation/src/PhysicalSimulation/Core)
add_subdirectory(PhysicalSimulation/src/PhysicalSimulation/Math)
add_subdirectory(PhysicalSimulation/src/PhysicalSimulation/Physics2D)
add_subdirectory(PhysicalSimulation/src/PhysicalSimulation/Renderer)
add_subdirectory(Sandbox/scenes)

add_executable(PhysicalSimApp PhysicalSimulation/src/PhysicalSimulation/Core/entryPoint.cpp)

target_link_libraries(PhysicalSimApp PRIVATE Core Math Physics2D Renderer imgui Scenes  "${CMAKE_SOURCE_DIR}/PhysicalSimulation/vendor/SDL3/libSDL3.dll.a")

add_custom_command(
    TARGET PhysicalSimApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources
    $<TARGET_FILE_DIR:PhysicalSimApp>/Resources
)  