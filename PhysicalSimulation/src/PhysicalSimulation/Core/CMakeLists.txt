﻿add_library(Core STATIC
    application.cpp
    entryPoint.cpp

)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Core PUBLIC Math Physics2D Renderer imgui Scenes)
