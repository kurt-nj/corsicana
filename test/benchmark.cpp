#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "corsicana/trie.hpp"

static constexpr int ITERATIONS = 4;
static constexpr int INPUT_COUNT = 10;
static constexpr int INPUT_SIZE = 256;
static constexpr int PATTERN_COUNT = 1000000;
static constexpr int PATTERN_SIZE = 8;

static const std::string NUMBERS = "0123456789";
static const std::string ALPHANUM = "0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

std::string generate(size_t len, std::string const& seed) {
    std::string str;
    for (size_t i = 0; i < len; ++i) {
        auto place = static_cast<size_t>(rand()) % (seed.size() - 1);
        str += seed[place];
    }
    return str;
}

size_t bench_naive(std::vector<std::string> const& text_strings,
                   std::vector<std::string> const& patterns) {
    size_t count = 0;
    for (auto const& text : text_strings) {
        for (auto const& pattern : patterns) {
            size_t pos = text.find(pattern);
            while (pos != std::string::npos) {
                count++;
                pos = text.find(pattern, pos+1);
            }
        }
    }
    return count;
}

size_t bench_corsicana(std::vector<std::string> const& text_strings,
                       corsicana::trie const& t) {
    size_t count = 0;
    for (auto const& text : text_strings) {
        auto matches = t.match(text).all();
        count += matches.size();
    }
    return count;
}

void benchmark(std::string const& seed) {
    using namespace std::chrono;

    std::cout << "Generating input text ..." << std::endl;
    // we first use a set to remove any duplicates
    std::set<std::string> input_set;
    for (int x=0; x<INPUT_COUNT; x++) {
        input_set.insert(generate(INPUT_SIZE, seed));
    }
    // transfer unique values to a vector for easy iteration
    std::vector<std::string> inputs(input_set.begin(), input_set.end());


    std::cout << "Generating search patterns ..." << std::endl;
    // we first use a set to remove any duplicates
    std::set<std::string> pattern_set;
    for (int x=0; x<PATTERN_COUNT; x++) {
        pattern_set.insert(generate(PATTERN_SIZE, seed));
    }
    // transfer unique values to a vector for easy iteration
    std::vector<std::string> patterns(pattern_set.begin(), pattern_set.end());

    std::cout << "Building trie..." << std::endl;
    auto trie_start = high_resolution_clock::now();
    corsicana::trie t;
    for (auto const& pattern : patterns) {
        t.insert(pattern);
    }
    t.freeze();
    auto trie_end = high_resolution_clock::now();
    auto trie_time = trie_end - trie_start;
    std::cout << "trie build time: " << duration_cast<milliseconds>(trie_time).count() << "ms" << std::endl;

    std::cout << "Running Benchmarks..." << std::endl;
    for (int x=0; x<ITERATIONS; x++) {
        std::cout << "Iteration #" << x;
        // naive run and measurements
        auto naive_start = high_resolution_clock::now();
        size_t count_1 = bench_naive(inputs, patterns);
        auto naive_end = high_resolution_clock::now();
        auto naive_time = naive_end - naive_start;
        std::cout << " naive: " << duration_cast<milliseconds>(naive_time).count() << "ms matches: " << count_1;

        // corsicana run and measurements
        auto corsicana_start = high_resolution_clock::now();
        size_t count_2 = bench_corsicana(inputs, t);
        auto corsicana_end = high_resolution_clock::now();
        auto corsicana_time = corsicana_end - corsicana_start;
        std::cout << " corsicana: " << duration_cast<milliseconds>(corsicana_time).count() << "ms matches: " << count_2;

        if (count_1 != count_2) {
            std::cout << " !!!FAILURE!!!" << std::endl;
        }
        std::cout << std::endl;
    }
}

int main() {

    // benchmark against a semi complete ASCII seed
    // this benchmarks the case of no matches (probably)
    std::cout << "*** Alphanum Benchmark ***" << std::endl;
    benchmark(ALPHANUM);

    // benchmark against a seed of just numbers
    // this benchmark will actually have matches (probably)
    std::cout << "*** Numbers Benchmark ***" << std::endl;
    benchmark(NUMBERS);

    return 0;
}