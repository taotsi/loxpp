include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/deps)

add_executable(clox main.c clox_chunk.c clox_memory.c clox_debug.c)

set_target_properties(clox PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})