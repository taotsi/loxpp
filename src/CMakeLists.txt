add_executable(loxpp main.cc chunk.cc debuger.cc value.cc vm.cc)

target_include_directories(loxpp PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(loxpp PUBLIC ${PROJECT_SOURCE_DIR}/extern)
target_include_directories(loxpp PUBLIC ${PROJECT_SOURCE_DIR}/extern/little-utility/)
target_include_directories(loxpp PUBLIC ${PROJECT_SOURCE_DIR}/extern/CLI)

set_target_properties(loxpp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})