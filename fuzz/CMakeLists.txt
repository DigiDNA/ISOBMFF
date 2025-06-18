# Include directories
include_directories(PUBLIC ../include)
include_directories(PUBLIC ../src)

# MacOS requirements
include_directories(PUBLIC /usr/local/include)
link_directories(/usr/local/lib)

# Add sanitizer options
add_compile_options(-fsanitize=address,fuzzer,undefined)
add_link_options(-fsanitize=address,fuzzer,undefined)

# Function to add a fuzzer executable
function(add_fuzzer TARGET SOURCE)
  if(NOT WIN32)
    add_executable(${TARGET} ${SOURCE})
    target_link_libraries(${TARGET} PUBLIC isobmff)
  endif()
endfunction()

# Add fuzzers
add_fuzzer(Parser_fuzzer Parser_fuzzer.cpp)
add_fuzzer(META_fuzzer META_fuzzer.cpp)
add_fuzzer(FTYP_fuzzer FTYP_fuzzer.cpp)
add_fuzzer(MVHD_fuzzer MVHD_fuzzer.cpp)
add_fuzzer(HDLR_fuzzer HDLR_fuzzer.cpp)
add_fuzzer(TKHD_fuzzer TKHD_fuzzer.cpp)
