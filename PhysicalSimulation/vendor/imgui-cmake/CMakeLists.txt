file(GLOB IMGUI_SOURCES
    ../imgui/imgui.cpp
    ../imgui/imgui_draw.cpp
    ../imgui/imgui_tables.cpp
    ../imgui/imgui_widgets.cpp
    ../imgui/backends/imgui_impl_sdl3.cpp
    ../imgui/backends/imgui_impl_sdlrenderer3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../imgui/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/../SDL3
)