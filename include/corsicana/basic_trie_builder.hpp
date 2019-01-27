#ifndef CORSICANA_BASIC_TRIE_BUILDER_HPP
#define CORSICANA_BASIC_TRIE_BUILDER_HPP

#include "corsicana/basic_trie.hpp"
#include "corsicana/internal/data.hpp"

namespace corsicana {

/// Constructs a new trie.
/// In order for the Aho-Corasick algorithm to work,
/// the trie structure has to be built and connected.
template <typename T>
class basic_trie_builder {
public:

    /// Insert a single element into the trie.
    /// Returns a reference to itself to allow chaining
    basic_trie_builder<T>& insert(T const& str) {
        data->insert(str);
        return *this;
    }

    /// Build and finalize the trie.
    /// Returns a new basic_trie to perform match operations
    basic_trie<T> build() {
        data->freeze();
        // move over our trie data to it's new owner
        basic_trie<T> trie(std::move(data));
        // reset the data so the builder can be reused if desired
        data.reset(new corsicana::internal::data<T>());
        return trie;
    }

private:
    std::unique_ptr<internal::data<T>> data { new corsicana::internal::data<T>() };
};

} // namespace corsicana

#endif //CORSICANA_BASIC_TRIE_BUILDER_HPP
