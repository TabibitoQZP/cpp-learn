cmake_minimum_required(VERSION 3.10)
project(cpp_learn)
add_executable(cpp_learn
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(cpp_learn PUBLIC
    libs
)