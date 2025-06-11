add_library(Physics2D STATIC
    src/collision/ps_aabb.cpp
    src/collision/ps_circle.cpp
    src/collision/ps_ccd.cpp
    src/collision/ps_detector.cpp
    src/collision/ps_distance_joint.cpp
    src/collision/ps_edge.cpp
    src/collision/ps_grid.cpp
    src/collision/ps_narrowphase.cpp
    src/collision/ps_point_joint.cpp
    src/collision/ps_polygon.cpp
    src/collision/ps_sap.cpp
    src/collision/ps_simplex.cpp
    src/collision/ps_tree.cpp
    
    src/dynamics/ps_body.cpp
    src/dynamics/ps_contact.cpp
    src/dynamics/ps_system.cpp
    src/dynamics/ps_world.cpp
)
target_include_directories(Physics2D PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/collision
    ${CMAKE_CURRENT_SOURCE_DIR}/include/dynamics
)
target_link_libraries(Physics2D PRIVATE Math)