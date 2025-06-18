cmake_minimum_required(VERSION 3.12)

# Define the project name and version
project(ISOBMFF VERSION 0.1)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Compiler selection
if(APPLE)
    message(STATUS "Using default Apple Clang on macOS.")
elseif(UNIX AND NOT APPLE)
    # Check for Clang first
    find_program(CLANG_C_COMPILER clang)
    find_program(CLANG_CXX_COMPILER clang++)
    if(CLANG_C_COMPILER AND CLANG_CXX_COMPILER)
        set(CMAKE_C_COMPILER ${CLANG_C_COMPILER})
        set(CMAKE_CXX_COMPILER ${CLANG_CXX_COMPILER})
        message(STATUS "Using Clang on Linux.")
    else()
        # Fallback to GNU if Clang is not found
        find_program(GNU_C_COMPILER gcc)
        find_program(GNU_CXX_COMPILER g++)
        if(GNU_C_COMPILER AND GNU_CXX_COMPILER)
            set(CMAKE_C_COMPILER ${GNU_C_COMPILER})
            set(CMAKE_CXX_COMPILER ${GNU_CXX_COMPILER})
            message(STATUS "Using GNU on Linux.")
        else()
            message(FATAL_ERROR "Neither Clang nor GNU compilers were found.")
        endif()
    endif()
endif()

# Verify the compiler
if(APPLE)
    if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        message(FATAL_ERROR "Apple Clang is required on macOS.")
    endif()
elseif(UNIX AND NOT APPLE)
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(FATAL_ERROR "This project requires either Clang or GNU as the C++ compiler on Linux.")
    endif()
endif()

# Add subdirectories for tests and fuzzers if enabled
add_subdirectory(src)
add_subdirectory(tools)

option(BUILD_TESTS "Build ISOBMFF tests" ON)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

option(BUILD_CLANG_FUZZER "Build clang fuzzer sanitizer targets" ON)
if(BUILD_CLANG_FUZZER)
  add_subdirectory(fuzz)
endif()
