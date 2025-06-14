add_library(Scenes STATIC
    src/scenes.cpp
    src/bitmask.cpp
    src/catapult.cpp
    src/heap.cpp
    src/newton_pendulum.cpp
    src/point_joint.cpp
    src/scenes.cpp
    src/simple.cpp
    src/scenes_joints.cpp
    src/sleep.cpp
)
target_include_directories(Scenes PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(Scenes PUBLIC Physics2D Renderer)