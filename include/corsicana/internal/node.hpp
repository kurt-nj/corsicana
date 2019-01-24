#ifndef CORSICANA_INTERNAL_NODE_HPP
#define CORSICANA_INTERNAL_NODE_HPP

#include <unordered_map>

namespace corsicana {
namespace internal {

template <class T>
struct node {
    std::unordered_map<T, node> children;
    T value;
    int word_index = 0;
    node<T>* parent = nullptr;
    node<T>* suffix_link = nullptr;
    node<T>* dict_suffix_link = nullptr;
};

} // namespace internal
} // namespace corsicana

#endif //CORSICANA_INTERNAL_NODE_HPP
