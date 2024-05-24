add_library(libs
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/vec.h"
)

set_target_properties(libs PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(libs PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/"
)