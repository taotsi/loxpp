add_executable(test_loxpp test_main.cc test_scanner.cc test_compiler.cc)

target_include_directories(test_loxpp PUBLIC ${include_dir})
target_include_directories(test_loxpp PUBLIC ${catch2_dir})
target_include_directories(test_loxpp PUBLIC ${utility_dir})

target_link_libraries(test_loxpp PRIVATE libloxpp)

if(MSVC)
  set_target_properties(test_loxpp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
  set_target_properties(test_loxpp PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR})
  set_target_properties(test_loxpp PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR})
else()
  set_target_properties(test_loxpp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif(MSVC)

add_definitions( -DTEST_SCRIPT_PATH="${PROJECT_SOURCE_DIR}/test/test_script.lx")
