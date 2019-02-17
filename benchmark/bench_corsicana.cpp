#include "bench_harness.hpp"
#include <memory>
#include "corsicana/trie.hpp"

class bench_corsicana : public bench_harness {
public:
    virtual void build(std::vector<std::string> const& patterns, size_t pattern_count) {
        corsicana::trie_builder tbuild(patterns.begin(), patterns.begin()+pattern_count);
        trie = std::unique_ptr<corsicana::trie>(new corsicana::trie(tbuild.build()));
    }

    virtual void run(std::vector<std::string> const& inputs) {
        size_t count = 0;
        for (auto const& text : inputs) {
            count += trie->match(text).count();
        }
    }

private:
    std::unique_ptr<corsicana::trie> trie;
};

int main() {
    bench_corsicana corsicana;
    corsicana.benchmark();
    return 0;
}