add_library(Renderer STATIC
    src/renderer.cpp
    src/camera.cpp
)

target_include_directories(Renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(Renderer PUBLIC Math imgui Physics2D)