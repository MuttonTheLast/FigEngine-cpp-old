cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)

link_directories(${CMAKE_BINARY_DIR}/lib/$<CONFIG>)

# INFO: Calculations

# Define a helper variable to mark desktop platforms

option(FIG_FORCE_DESKTOP "Force include desktop things" FALSE)
set(IS_DESKTOP ${FIG_FORCE_DESKTOP})
if (NOT ${FIG_FORCE_DESKTOP})
    if(NOT CMAKE_SYSTEM_NAME)
        if (WIN32)
            set(WINDOWS TRUE)
            set(IS_DESKTOP TRUE)
        elseif (LINUX)
            set(LINUX TRUE)
            set(IS_DESKTOP TRUE)
        elseif (APPLE)
            set(MACOS TRUE)
            set(IS_DESKTOP TRUE)
        endif()
        message(WARNING "There is no toolchain. If you want to compile for a desktop its ok.")
    else()
        if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
            set(LINUX TRUE)
            set(IS_DESKTOP TRUE)
        elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
            set(WINDOWS TRUE)
            set(IS_DESKTOP TRUE)
        elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
            set(MACOS TRUE)
            set(IS_DESKTOP TRUE)
        elseif (CMAKE_SYSTEM_NAME STREQUAL "iOS")
            set(IOS TRUE)
        elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
            set(ANDROID TRUE)
        endif()
    endif()
endif()
message(STATUS "Desktop included: ${IS_DESKTOP}")



# INFO: End Calculations

project(FigEngine VERSION 0.1.0 LANGUAGES CXX)
#"a = Alpha, b = Beta, rc[num] = Release Candidate[num], (empty) = Release"
set(PROJECT_VERSION_SUFFIX "a")
if(${PROJECT_VERSION_SUFFIX} STREQUAL "")
    set(PROJECT_VERSION_FULL "${PROJECT_VERSION}")
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

