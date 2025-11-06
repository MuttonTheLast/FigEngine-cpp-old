cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)

link_directories(${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
project(FigEngine VERSION 0.1.0 LANGUAGES CXX)
#"a = Alpha, b = Beta, rc[num] = Release Candidate[num], (empty) = Release"
set(PROJECT_VERSION_SUFFIX "a")
if(${PROJECT_VERSION_SUFFIX} STREQUAL "")
    set(PROJECT_VERSION_FULL "${PROJECT_VERSION}${PROJECT_VERSION_SUFFIX}")
else()
    set(PROJECT_VERSION_FULL "${PROJECT_VERSION}-${PROJECT_VERSION_SUFFIX}")
endif()

configure_file(FigConfig.h.in FigConfig.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# externals
add_subdirectory(external/SDL3)
add_subdirectory(external/glm)
add_subdirectory(external/quill)

add_subdirectory(Unit_Tests)
add_subdirectory(Fig)

