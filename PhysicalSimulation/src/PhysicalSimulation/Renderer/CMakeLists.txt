add_library(Renderer STATIC
    renderer.cpp
    camera.cpp
)

target_include_directories(Renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(Renderer PUBLIC Math imgui Physics2D)