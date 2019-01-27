#ifndef CORSICANA_BASIC_TRIE_HPP
#define CORSICANA_BASIC_TRIE_HPP

#include "corsicana/match.hpp"
#include "corsicana/internal/data.hpp"

namespace corsicana {

// forward declaration
template<class T>
class basic_trie_builder;

/// Holds the built Aho-Corasick trie
template <typename T>
class basic_trie {
public:

    friend class basic_trie_builder<T>;

    /// Perform a match search on the constructed trie.
    /// At this point the trie data is read only.
    corsicana::match<T> match(T const& text) const {
        return corsicana::match<T>(text, *data);
    }

private:

    basic_trie(std::unique_ptr<internal::data<T>> data_in) {
        data = std::move(data_in);
    }

    std::unique_ptr<internal::data<T>> data;
};

} // namespace corsicana

#endif //CORSICANA_BASIC_TRIE_HPP
