add_library(Math STATIC
    src/ps_algorithm_2d.cpp
    src/ps_common.cpp
    src/ps_math.cpp
    src/ps_vector2.cpp
    src/ps_vector3.cpp
    src/ps_vector4.cpp
    src/ps_matrix2x2.cpp
    src/ps_matrix3x3.cpp
    src/ps_matrix4x4.cpp
    src/ps_integrator.cpp
)
target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)