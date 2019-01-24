

SET(TEST_SRC
    test_main.cpp
    test_match.cpp
    test_match_state.cpp
    test_data.cpp
    test_trie_types.cpp
)

set(COMPILER_FLAGS
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wconversion
    -Wsign-conversion
    -Wformat=2
    -Werror
)

add_executable(corsicana_test ${TEST_SRC})
target_link_libraries(corsicana_test corsicana)
target_compile_options(corsicana_test PUBLIC ${COMPILER_FLAGS})
add_test(NAME corsicana_test COMMAND $<TARGET_FILE:corsicana_test>)

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark corsicana)
target_compile_options(benchmark PUBLIC ${COMPILER_FLAGS})
