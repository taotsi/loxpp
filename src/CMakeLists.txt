include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/deps)

add_executable(clox main.cc clox_chunk.cc clox_memory.cc clox_debug.cc)

set_target_properties(clox PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})