add_library(SDL3 SHARED IMPORTED)

set_target_properties(SDL3 PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/PhysicalSimulation/vendor/SDL3/SDL3.dll"
    IMPORTED_IMPLIB  "${CMAKE_SOURCE_DIR}/PhysicalSimulation/vendor/SDL3/libSDL3.dll.a"
)

target_include_directories(SDL3 INTERFACE
    ${CMAKE_SOURCE_DIR}/PhysicalSimulation/vendor/SDL3
)