cmake_minimum_required(VERSION 3.7)

project(loxpp VERSION 0.1 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(include_dir ${PROJECT_SOURCE_DIR}/include)
set(utility_dir ${PROJECT_SOURCE_DIR}/extern/little-utility/include/little-utility)
set(catch2_dir ${PROJECT_SOURCE_DIR}/extern/Catch2/single_include/catch2)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(
  NAME test_loxpp
  COMMAND $<TARGET_FILE:test_loxpp> --success
)
