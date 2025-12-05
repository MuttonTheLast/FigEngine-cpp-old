cmake_minimum_required(VERSION 3.16)

add_executable(Test main.cpp)

target_link_libraries(Test 
    Fig
)
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_BINARY_DIR}/$<CONFIG>/assets/
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Unit_Tests/Test/assets
            ${CMAKE_BINARY_DIR}/$<CONFIG>/assets/)



