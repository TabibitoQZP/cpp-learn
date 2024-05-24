add_library(libs
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/vec.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/vec.cpp"
)

target_include_directories(libs PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/"
)