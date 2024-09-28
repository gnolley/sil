cmake_minimum_required(VERSION 3.26.4)

project(
    Soliloquy
    VERSION 0.0.1
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

set(ENGINE_SRC_TARGET Sil-Core)
set(BOOTSTRAP_TARGET Sil-Bootstrapper)

option(BUILD_UNIT_TESTS "Build unit tests with build" OFF)
option(ENABLE_WARNINGS "Build unit tests with build" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Build unit tests with build" ON)

option(ENABLE_SANITIZE_ADDR "Enable Address Sanitiser" OFF)
option(ENABLE_SANITIZE_UNDEF "Enable Undefined Sanitiser" OFF)
option(ENABLE_LTO "Enable Link Time Optimisation" OFF)

include(ConfigSafeGuard)

if(${ENABLE_WARNINGS})
    include(Warnings)
endif()

if(${ENABLE_SANITIZE_ADDR} OR ${ENABLE_SANITIZE_UNDEF})
    include(Sanitisers)
    add_santiser_flags()
endif()

if(${ENABLE_LTO})
    include(LTO)
endif()

add_subdirectory(config)
add_subdirectory(engine)
add_subdirectory(bootstrap)

if(BUILD_UNIT_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()