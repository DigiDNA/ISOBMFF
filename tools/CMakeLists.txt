add_executable(isobmff-bin main.cpp)
target_include_directories(isobmff-bin PUBLIC ../src)
target_link_libraries(isobmff-bin PUBLIC isobmff)
# rename executable using target properties
set_target_properties(isobmff-bin PROPERTIES OUTPUT_NAME isobmff)
