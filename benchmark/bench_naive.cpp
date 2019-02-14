#include "bench_harness.hpp"
#include <memory>
#include "corsicana/trie.hpp"

class bench_naive : public bench_harness {
public:
    virtual void build(std::vector<std::string> const& patterns, size_t pattern_count) {
        search_patterns = std::vector<std::string>(patterns.begin(), patterns.begin()+pattern_count);
    }

    virtual void run(std::vector<std::string> const& inputs) {
        size_t count = 0;
        for (auto const& text : inputs) {
            for (auto const& pattern : search_patterns) {
                size_t pos = text.find(pattern);
                while (pos != std::string::npos) {
                    count++;
                    pos = text.find(pattern, pos+1);
                }
            }
        }
    }

private:
    std::vector<std::string> search_patterns;
};

int main() {
    bench_naive naive;
    naive.benchmark();
    return 0;
}