
##############################################
# Test Source
##############################################
SET(TEST_SRC
    test_main.cpp
    test_match.cpp
    test_match_state.cpp
    test_data.cpp
    test_basic_trie_builder.cpp
    test_basic_trie.cpp
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
    -g
)

##############################################
# Unit Test Executable (Catch2)
##############################################
add_executable(corsicana_test ${TEST_SRC})
target_link_libraries(corsicana_test PUBLIC corsicana)
target_compile_options(corsicana_test PUBLIC ${COMPILER_FLAGS})
add_test(NAME corsicana_test COMMAND $<TARGET_FILE:corsicana_test>)

##############################################
# Generate code coverage
##############################################
if(CODE_COVERAGE)
    target_compile_options(corsicana_test PUBLIC -O0 --coverage)
    target_link_libraries(corsicana_test PUBLIC gcov --coverage)
endif(CODE_COVERAGE)
