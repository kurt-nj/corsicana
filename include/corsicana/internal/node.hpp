#ifndef CORSICANA_INTERNAL_NODE_HPP
#define CORSICANA_INTERNAL_NODE_HPP

#include <unordered_map>
#include <memory>

namespace corsicana {
namespace internal {

// Internal class that represents a node in the trie
// API subject to change. Not intended for general usage.
template <class T>
struct node {

    using TValue = typename T::value_type;

    // map of all children to this node
    std::unordered_map<TValue, std::unique_ptr<node<T>>> children;
    // node value
    TValue value;
    // pointer back to the full word
    const T* word = nullptr;
    // link back up to the parent
    node<T>* parent = nullptr;
    // link to the longest substring in the trie
    // points to root if no substring exists
    node<T>* suffix_link = nullptr;
    // link to the longest substring that is a whole word
    // points to null if none exists
    node<T>* dict_suffix_link = nullptr;
};

} // namespace internal
} // namespace corsicana

#endif //CORSICANA_INTERNAL_NODE_HPP
