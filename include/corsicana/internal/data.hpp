#ifndef CORSICANA_INTERNAL_DATA_HPP
#define CORSICANA_INTERNAL_DATA_HPP

#include <unordered_map>
#include <queue>
#include "corsicana/internal/node.hpp"

namespace corsicana {
namespace internal {

template <class T>
class data {
public:

    // The value type associated with our template type
    using TValue = typename T::value_type;

    ///
    void insert(T const& text) {
        if(!text.empty()) {
            dictionary.emplace(++counter, text);
        }
    }

    T const& get(int index) const {
        auto it = dictionary.find(index);
        return it->second;
    }

    const corsicana::internal::node<TValue>* root_node() const {
        return &root;
    }

    void freeze() {
        build_trie();
        std::queue<node<TValue>*> dfs;
        dfs.push(&root);
        while (!dfs.empty()) {
            auto node = dfs.front();
            dfs.pop();

            calc_suffix(node);

            for (auto& child : node->children) {
                dfs.push(child.second.get());
            }
        }
        frozen = true;
    }

private:

    void build_trie() {
        // for each of our inserted strings, build our trie!
        for (const auto& pair : dictionary) {
            const auto& str = pair.second;

            auto current = &root;
            for (TValue c : str) {
                // look for next character=
                auto it = current->children.find(c);
                if (it == current->children.end()) {
                    // create a new node if this character doesn't yet exist
                    std::unique_ptr<node<TValue>> node(new corsicana::internal::node<TValue>());
                    node->value = c;
                    node->parent = current;
                    current->children.emplace(c,std::move(node));
                }
                current = current->children[c].get();
            }
            // the node is the end of our word
            current->word_index = pair.first;
        }
    }


    void calc_suffix(corsicana::internal::node<TValue>* node) {
        // root is the suffix of itself
        if (node == &root) {
            node->suffix_link = node;
        }
        // children of root have the root as a suffix
        // the suffix of a one character string (e.g. "a") is an empty string ("")
        else if (node->parent == &root) {
            node->suffix_link = node->parent;
        }
        else {
            // follow the already calculated parent suffix
            auto* current_best = node->parent->suffix_link;
            auto current_val = node->value;

            while(node->suffix_link == nullptr) {
                auto it = current_best->children.find(current_val);
                if (it != current_best->children.end()) {
                    node->suffix_link = it->second.get();
                }
                else if (current_best == &root) {
                    node->suffix_link = current_best;
                }
                current_best = current_best->suffix_link;
            }

            if (node->suffix_link->word_index != 0) {
                node->dict_suffix_link = node->suffix_link;
            }
            else {
                node->dict_suffix_link = node->suffix_link->dict_suffix_link;
            }

        }
    }

    node<TValue> root;
    std::unordered_map<int,T> dictionary;
    bool frozen = false;
    int counter = 0;
};
} // namespace internal
} // namespace corsicana

#endif //CORSICANA_INTERNAL_DATA_HPP
