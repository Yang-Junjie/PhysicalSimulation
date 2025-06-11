add_library(Core STATIC
    src/application.cpp
    src/entryPoint.cpp

)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inclued
)

target_link_libraries(Core PUBLIC Math Physics2D Renderer imgui Scenes)
