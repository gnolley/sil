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

set(SIL_DEBUG_FLAG SIL_DEBUG)
set(SIL_RELEASE_FLAG SIL_RELEASE)
set(SIL_VK_LAYERS_FLAG SIL_ENABLE_GFX_VALIDATION_LAYERS)

include(ConfigSafeGuard)

option(BUILD_UNIT_TESTS "Build unit tests with build" OFF)
option(ENABLE_WARNINGS "Build unit tests with build" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Build unit tests with build" ON)

option(ENABLE_SANITIZE_ADDR "Enable Address Sanitiser" OFF)
option(ENABLE_SANITIZE_UNDEF "Enable Undefined Sanitiser" OFF)
option(ENABLE_VK_VALIDATION_LAYERS "Enable Vulkan Validation Layers" ON)

option(ENABLE_LTO "Enable Link Time Optimisation" OFF)

if(${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")

option(ENABLE_SANITIZE_ADDR "Enable Address Sanitiser" ON)
option(ENABLE_SANITIZE_UNDEF "Enable Undefined Sanitiser" ON)
option(ENABLE_VK_VALIDATION_LAYERS "Enable Vulkan Validation Layers" ON)

elseif(${CMAKE_BUILD_TYPE} STREQUAL "RELEASE")

option(ENABLE_SANITIZE_ADDR "Enable Address Sanitiser" OFF)
option(ENABLE_SANITIZE_UNDEF "Enable Undefined Sanitiser" OFF)
option(ENABLE_VK_VALIDATION_LAYERS "Enable Vulkan Validation Layers" OFF)

endif()



include(FindVulkan)
if(${Vulkan_FOUND})
    message(STATUS "Vulkan Found!")
else()
    message(FATAL_ERROR "Could not find vulkan sdk!")
endif()

include ($ENV{VCPKG_ROOT}\\scripts\\buildsystems\\vcpkg.cmake)
find_package(glfw3 CONFIG REQUIRED)

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