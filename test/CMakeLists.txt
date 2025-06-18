# Enable testing
enable_testing()
# Find GTest package
find_package(GTest REQUIRED)
# Include directories
include_directories(PUBLIC ../src)
# MacOS requirements
include_directories(PUBLIC /usr/local/include)
link_directories(/usr/local/lib)

# Function to add a test executable
function(add_isobmff_test test_name)
  add_executable(${test_name} ${test_name}.cpp)
  add_test(NAME ${test_name} COMMAND ${test_name})
  target_link_libraries(${test_name} PUBLIC isobmff GTest::gtest GTest::gtest_main)
endfunction()

# List of test names
set(TEST_NAMES
    Parser_unittest
    META_unittest
    FTYP_unittest
    MVHD_unittest
    HDLR_unittest
    TKHD_unittest
)
# Add tests
foreach(test_name IN LISTS TEST_NAMES)
  add_isobmff_test(${test_name})
endforeach()
