message (STATUS "Binary Directory: ${CMAKE_BINARY_DIR}")

configure_file(
    "Config.hpp.in"
    "${CMAKE_BINARY_DIR}/configured_files/include/Config.hpp" ESCAPE_QUOTES
)