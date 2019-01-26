#ifndef CORSICANA_BASIC_TRIE_BUILDER_HPP
#define CORSICANA_BASIC_TRIE_BUILDER_HPP

#include "corsicana/basic_trie.hpp"
#include "corsicana/internal/data.hpp"

namespace corsicana {

template <typename T>
class basic_trie_builder {
public:

    basic_trie_builder<T>& insert(T const& str) {
        data->insert(str);
        return *this;
    }

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
