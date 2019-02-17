
add_executable(bench_corsicana bench_corsicana.cpp bench_harness.hpp)
target_link_libraries(bench_corsicana corsicana)
target_compile_options(bench_corsicana PUBLIC -Wall -Wextra -O2)

add_executable(bench_naive bench_naive.cpp bench_harness.hpp)
target_link_libraries(bench_naive corsicana)
target_compile_options(bench_naive PUBLIC -Wall -Wextra -O2)