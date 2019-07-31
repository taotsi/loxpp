include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/deps)

add_executable(loxpp main.cc chunk.cc debug.cc value.cc vm.cc)

set_target_properties(loxpp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})