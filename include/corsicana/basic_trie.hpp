#ifndef CORSICANA_BASIC_TRIE_HPP
#define CORSICANA_BASIC_TRIE_HPP

#include "corsicana/match.hpp"
#include "corsicana/internal/data.hpp"

namespace corsicana {

template <typename T>
class basic_trie {
public:

    basic_trie<T>& insert(T const& str) {
        data.insert(str);
        return *this;
    }

    void freeze() {
        data.freeze();
    }

    corsicana::match<T> match(T const& text) const {
        return corsicana::match<T>(text, data);
    }

private:
    corsicana::data<T> data;
};

} // namespace corsicana

#endif //CORSICANA_BASIC_TRIE_HPP
