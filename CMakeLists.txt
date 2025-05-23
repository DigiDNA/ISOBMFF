cmake_minimum_required(VERSION 3.12)

# https://cmake.org/cmake/help/v3.0/command/project.html
project(ISOBMFF VERSION 0.1 LANGUAGES CXX)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Source files
file(GLOB_RECURSE ISOBMFF_SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ISOBMFF/source/*.cpp)


# Include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ISOBMFF/include)

# Create the library
add_library(ISOBMFF ${ISOBMFF_SRC})

# https://cmake.org/cmake/help/latest/guide/tutorial/index.html#adding-a-version-number-and-configured-header-file
configure_file(ISOBMFF/source/config.h.in ISOBMFF/source/config.h)

# Specify include directories for consumers
target_include_directories(ISOBMFF PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ISOBMFF/include>
    $<INSTALL_INTERFACE:include>
)

# Optional compiler flags
target_compile_features(ISOBMFF PUBLIC cxx_std_14)
