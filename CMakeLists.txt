cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ISOBMFF
  VERSION 0.1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE ISOBMFF_SOURCES
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/ISOBMFF/source/*.cpp"
)

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE ${ISOBMFF_SOURCES})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ISOBMFF/include>"
    "$<INSTALL_INTERFACE:include>"
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -fno-strict-aliasing)

option(ISOBMFF_BUILD_TESTS "Build ISOBMFF unit tests" ON)

if(ISOBMFF_BUILD_TESTS)
  enable_testing()

  set(XSTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Submodules/XSTest/XSTest/include")
  if(NOT EXISTS "${XSTEST_INCLUDE_DIR}/XSTest/XSTest.hpp")
    message(FATAL_ERROR "XSTest submodule not initialized — run `git submodule update --init Submodules/XSTest`")
  endif()

  file(GLOB ISOBMFF-Tests_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/ISOBMFF-Tests/*.cpp"
  )

  add_executable(ISOBMFF-Tests ${ISOBMFF-Tests_SOURCES})
  target_include_directories(ISOBMFF-Tests PRIVATE "${XSTEST_INCLUDE_DIR}")
  target_link_libraries(ISOBMFF-Tests PRIVATE ${PROJECT_NAME})
  target_compile_options(ISOBMFF-Tests PRIVATE -fpermissive)
  # XSTest provides main() when XSTEST_MAIN is defined (single test TU)
  target_compile_definitions(ISOBMFF-Tests PRIVATE XSTEST_MAIN)

  add_test(NAME ISOBMFF-Tests COMMAND ISOBMFF-Tests)
endif()
