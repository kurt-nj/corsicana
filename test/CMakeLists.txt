

SET(TEST_SRC
  test_main.cpp
  test_trie_search.cpp
  test_match_state.cpp
)

add_executable(corsicana_test ${TEST_SRC})
target_link_libraries(corsicana_test corsicana)
#add_test(NAME corsicana_test COMMAND $<TARGET_FILE:corsicana_test>)
add_test(NAME corsicana_test COMMAND $<TARGET_FILE:corsicana_test>)

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark corsicana)
