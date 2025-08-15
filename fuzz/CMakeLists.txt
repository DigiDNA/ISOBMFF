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

# Find all fuzzer files in the current directory
file(GLOB FUZZER_FILES "*_fuzzer.cpp")
# Extract fuzzer names from file names and add them
foreach(fuzzer_file IN LISTS FUZZER_FILES)
  get_filename_component(fuzzer_name ${fuzzer_file} NAME_WE)
  add_fuzzer(${fuzzer_name} ${fuzzer_file})
endforeach()
