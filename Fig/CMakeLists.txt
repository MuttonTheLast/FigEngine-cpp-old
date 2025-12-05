cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE FIG_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_library(Fig STATIC ${FIG_SOURCES})

target_include_directories(Fig
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_precompile_headers(Fig
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h
)


target_link_directories(Fig 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/
)

target_link_libraries(Fig 
    PUBLIC SDL3::SDL3
    PUBLIC glm::glm
    PUBLIC quill::quill
)

if (${IS_DESKTOP})
    target_link_libraries(Fig
        PUBLIC SDL3_shadercross-static
    )
    target_link_libraries(Fig PRIVATE dxcompiler spirv-cross-c-shared)

endif()

