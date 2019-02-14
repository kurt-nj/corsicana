#include <set>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <tuple>

// base class to implement benchmarking of the aho corasick algorithm in a consistent manner
// outputs build and run times in a CSV format for sorta easy graphing
class bench_harness {
public:

    static constexpr int PATTERN_SIZE = 10;
    static constexpr int INPUT_COUNT = 10;
    static constexpr int INPUT_SIZE = 256;

    virtual ~bench_harness() = default;

    // Generates unique string patterns
    std::vector<std::string> generate(size_t len, size_t num) {

        static const std::string ALPHANUM = "0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis(0, ALPHANUM.size()-1);
        std::set<std::string> unique;

        // continue creating until we get the correct number of UNIQUE strings
        while (unique.size() < num) {
            std::string str;
            for (size_t i = 0; i < len; ++i) {
                str += ALPHANUM[dis(gen)];
            }
            unique.insert(str);
        }
        return std::vector<std::string>(unique.begin(), unique.end());
    }

    // perform one step of the iteration
    // takes vectors of inputs and patterns but only uses the pattern_count number of patterns when creating the trie
    // this is done to reduce run times by not requiring us to generate additional patterns
    // Returns a tuple of build time and run time
    std::tuple<size_t, size_t> bench_iteration(
            size_t pattern_count,
            std::vector<std::string> const& inputs,
            std::vector<std::string> const& patterns) {
        using namespace std::chrono;

        auto bstart = high_resolution_clock::now();
        build(patterns, pattern_count);
        auto bend = high_resolution_clock::now();
        auto btime = bend - bstart;

        auto start = high_resolution_clock::now();
        run(inputs);
        auto end = high_resolution_clock::now();
        auto time = end - start;
        return std::make_tuple(duration_cast<nanoseconds>(btime).count(), duration_cast<nanoseconds>(time).count());
    }

    void benchmark() {

        auto inputs = generate(INPUT_SIZE, INPUT_COUNT);
        auto patterns = generate(PATTERN_SIZE, max_patterns());

        std::vector<std::tuple<size_t,size_t>> results;

        std::cout << "Running benchmark";
        for (size_t x=pattern_increment(); x<max_patterns(); x+=pattern_increment()) {
            results.push_back(bench_iteration(x, inputs, patterns));
            std::cout << ".";
        }

        std::cout << std::endl << "Build Times:" << std::endl;
        for (auto t : results) {
            std::cout << std::get<0>(t) << ", " ;
        }

        std::cout << std::endl << "Run Times:" << std::endl;
        for (auto t : results) {
            std::cout << std::get<1>(t) << ", " ;
        }
        std::cout << std::endl;
    }

    // implements the build for this implementation
    virtual void build(std::vector<std::string> const& patterns, size_t pattern_count) = 0;
    // implements the matching for this implementation
    virtual void run(std::vector<std::string> const& inputs) = 0;

    static constexpr size_t DEFAULT_MAX_PATTERNS = 3000000;
    virtual size_t max_patterns() { return DEFAULT_MAX_PATTERNS; }

    static constexpr size_t DEFAULT_PATTERN_INCREMENT = 300000;
    virtual size_t pattern_increment() { return DEFAULT_PATTERN_INCREMENT; }
};