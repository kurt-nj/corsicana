#ifndef CORSICANA_INTERNAL_DATA_HPP
#define CORSICANA_INTERNAL_DATA_HPP

#include <unordered_map>
#include <queue>
#include "corsicana/internal/node.hpp"

namespace corsicana {
namespace internal {

// Internal object that stores the underlining trie structure.
// API subject to change. Not intended for general usage.
template <class T>
class data {
public:

    // The value type associated with our template type
    using TValue = typename T::value_type;

    // Insert a value into the backing dictionary
    // Should not get called after freezing
    void insert(T const& text) {
        if(!text.empty()) {
            dictionary.emplace_back(text);
        }
    }

    // Returns a pointer to our root node
    const corsicana::internal::node<T>* root_node() const {
        return &root;
    }

    // Freeze and build our trie.
    // Constructs our trie from our dictionary and performs the final linkage
    // Should only get called once
    void freeze() {
        build_trie();
        // perform a depth first search to search every node in order of depth
        std::queue<node<T>*> dfs;
        dfs.push(&root);
        while (!dfs.empty()) {
            auto node = dfs.front();
            dfs.pop();
            // calculate the linkage for this node. is dependent on parent nodes already linked
            calc_suffix(node);
            // add child nodes to queue
            for (auto& child : node->children) {
                dfs.push(child.second.get());
            }
        }
    }

    // Return the size of the dictionary
    size_t size() const {
        return dictionary.size();
    }

private:

    void build_trie() {
        // for each of our inserted strings, build our trie!
        for (const auto& str : dictionary) {

            auto current = &root;
            for (TValue c : str) {
                // look for next character
                auto it = current->children.find(c);
                if (it == current->children.end()) {
                    // create a new node if this character doesn't yet exist
                    std::unique_ptr<node<T>> node(new corsicana::internal::node<T>());
                    node->value = c;
                    node->parent = current;
                    current->children.emplace(c,std::move(node));
                }
                current = current->children[c].get();
            }
            // the node is the end of our word
            current->word = &str;
        }
    }


    void calc_suffix(corsicana::internal::node<T>* node) {
        // root is the suffix of itself
        if (node == root_node()) {
            node->suffix_link = node;
        }
        // children of root have the root as a suffix
        // the suffix of a one character string (e.g. "a") is an empty string ("")
        else if (node->parent == root_node()) {
            node->suffix_link = node->parent;
        }
        else {
            // follow the already calculated parent suffix
            auto* current_best = node->parent->suffix_link;
            auto current_val = node->value;
            while(node->suffix_link == nullptr) {
                // if the parent's suffix also has this node value, go there
                auto it = current_best->children.find(current_val);
                if (it != current_best->children.end()) {
                    node->suffix_link = it->second.get();
                }
                // if we hit root, then that is all folks
                else if (current_best == root_node()) {
                    node->suffix_link = current_best;
                }
                // keep traveling up suffix links to try and find a match
                current_best = current_best->suffix_link;
            }
            // find the longest full word suffix if it exists
            if (node->suffix_link->word) {
                node->dict_suffix_link = node->suffix_link;
            }
            else {
                node->dict_suffix_link = node->suffix_link->dict_suffix_link;
            }

        }
    }

    node<T> root;
    std::vector<T> dictionary;
};
} // namespace internal
} // namespace corsicana

#endif //CORSICANA_INTERNAL_DATA_HPP
