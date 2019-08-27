add_library(libloxpp chunk.cc debuger.cc value.cc vm.cc)

target_include_directories(libloxpp PUBLIC ${include_dir})
target_include_directories(libloxpp PUBLIC ${utility_dir})

add_executable(loxpp main.cc)

target_link_libraries(loxpp PRIVATE libloxpp)

target_include_directories(loxpp PUBLIC ${include_dir})
target_include_directories(loxpp PUBLIC ${utility_dir})

set_target_properties(loxpp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})