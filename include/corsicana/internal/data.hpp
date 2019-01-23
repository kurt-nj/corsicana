#ifndef CORSICANA_INTERNAL_DATA_HPP
#define CORSICANA_INTERNAL_DATA_HPP

#include <unordered_map>
#include <queue>
#include "corsicana/internal/node.hpp"

namespace corsicana {

template <class T>
class data {
public:

    using TType = typename T::value_type;

    void insert(T const& text) {
        if(!text.empty()) {
            dictionary.emplace(++counter, text);
        }
    }

    T const& get(int index) const {
        auto it = dictionary.find(index);
        return it->second;
    }

    const corsicana::node<TType>* root_node() const {
        return &root;
    }

    void freeze() {
        build_trie();
        std::queue<corsicana::node<TType>*> dfs;
        dfs.push(&root);
        while (!dfs.empty()) {
            auto node = dfs.front();
            dfs.pop();

            //std::cout << "calc on " << node->value << std::endl;
            calc_suffix(node);

            for (auto& child : node->children) {
                dfs.push(&child.second);
            }
        }
        frozen = true;
    }

private:

    void build_trie() {
        // for each of our inserted strings, build our trie!
        for (const auto& pair : dictionary) {
            const auto& str = pair.second;
            //std::cout << "INSERT " << str << std::endl;

            auto current = &root;
            for (char c : str) {
                // look for next character
                auto it = current->children.find(c);
                if (it == current->children.end()) {
                    // create a new node if this character doesn't yet exist
                    corsicana::node<TType> node;
                    node.value = c;
                    node.parent = current;
                    current->children.emplace(c,node);
                    //std::cout << "add " << c << " to " << current->value << std::endl;
                }
                //else {
                //    std::cout << "found " << c << " on " << current->value << std::endl;
                //}
                current = &current->children[c];
            }
            // the node is the end of our word
            current->word_index = pair.first;
        }
    }


    void calc_suffix(corsicana::node<TType>* node) {
        // root is the suffix of itself
        if (node == &root) {
            //std::cout << "root is root" << std::endl;
            node->suffix_link = node;
        }
        // children of root have the root as a suffix
        // the suffix of a one character string (e.g. "a") is an empty string ("")
        else if (node->parent == &root) {
            //std::cout << node->value << " is child of root" << std::endl;
            node->suffix_link = node->parent;
        }
        else {
            // follow the already calculated parent suffix
            auto* current_best = node->parent->suffix_link;
            auto current_val = node->value;

            //std::cout << "looking for " << node->value << " child of " << node->parent->value << " off of " << current_best->value << std::endl;

            while(node->suffix_link == nullptr) {
                auto it = current_best->children.find(current_val);
                if (it != current_best->children.end()) {
                    //std::cout << "found suffix for " << node->value << " off of " << current_best->value << std::endl;
                    node->suffix_link = &it->second;
                }
                else if (current_best == &root) {
                    //std::cout << "found suffix for " << node->value << " off of root " << std::endl;
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

    corsicana::node<TType> root;
    std::unordered_map<int,T> dictionary;
    bool frozen = false;
    int counter = 0;
};

} // namespace corsicana

#endif //CORSICANA_INTERNAL_DATA_HPP
