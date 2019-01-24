#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include "corsicana/trie.hpp"

static constexpr int ITERATIONS = 10;
static constexpr int INPUT_COUNT = 10;
static constexpr int INPUT_SIZE = 256;
static constexpr int PATTERN_COUNT = 1000000;
static constexpr int PATTERN_SIZE = 8;

using ms = std::chrono::milliseconds;

std::string generate(size_t len) {
    static const std::string alphanum =
        "0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::string str;
    for (size_t i = 0; i < len; ++i) {
        auto place = static_cast<size_t>(rand()) % (sizeof(alphanum) - 1);
        str += alphanum[place];
    }
    return str;
}

size_t bench_naive(std::vector<std::string> const& text_strings,
                   std::vector<std::string> const& patterns) {
    size_t count = 0;
    for (auto const& text : text_strings) {
        for (auto const& pattern : patterns) {
            size_t pos = text.find(pattern);
            while (pos != text.npos) {
                pos = text.find(pattern, pos);
                count++;
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

int main() {
    std::cout << "*** Corsicana Benchmark ***" << std::endl;

    std::cout << "Generating input text ..." << std::endl;
    std::vector<std::string> inputs;
    for (int x=0; x<INPUT_COUNT; x++) {
        inputs.push_back(generate(INPUT_SIZE));
    }

    std::cout << "Generating search patterns ..." << std::endl;
    std::vector<std::string> patterns;
    for (int x=0; x<PATTERN_COUNT; x++) {
        patterns.push_back(generate(PATTERN_SIZE));
    }

    std::cout << "Building trie..." << std::endl;
    auto trie_start = std::chrono::high_resolution_clock::now();
    corsicana::trie t;
    for (auto const& pattern : patterns) {
        t.insert(pattern);
    }
    t.freeze();
    auto trie_end = std::chrono::high_resolution_clock::now();
    auto trie_time = trie_end - trie_start;
    std::cout << "trie build time: " << std::chrono::duration_cast<ms>(trie_time).count() << "ms" << std::endl;

    std::cout << "Running Benchmarks..." << std::endl;
    for (int x=0; x<ITERATIONS; x++) {
        std::cout << "Iteration #" << x;
        auto naive_start = std::chrono::high_resolution_clock::now();
        size_t count_1 = bench_naive(inputs, patterns);
        auto naive_end = std::chrono::high_resolution_clock::now();
        auto naive_time = naive_end - naive_start;
        std::cout << " naive: " << std::chrono::duration_cast<ms>(naive_time).count() << "ms";

        auto corsicana_start = std::chrono::high_resolution_clock::now();
        size_t count_2 = bench_corsicana(inputs, t);
        auto corsicana_end = std::chrono::high_resolution_clock::now();
        auto corsicana_time = corsicana_end - corsicana_start;
        std::cout << " corsicana: " << std::chrono::duration_cast<ms>(corsicana_time).count() << "ms";

        if (count_1 != count_2) {
            std::cout << " !!!FAILURE!!!" << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
