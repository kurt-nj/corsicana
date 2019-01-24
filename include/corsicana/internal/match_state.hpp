#ifndef CORSICANA_INTERNAL_MATCH_STATE_HPP
#define CORSICANA_INTERNAL_MATCH_STATE_HPP

#include "corsicana/internal/data.hpp"
#include "corsicana/internal/node.hpp"

namespace corsicana {
namespace internal {

template <class T>
class match_state {
public:

    using TValue = typename T::value_type;
    using TSize = typename T::size_type;

    match_state(T const& text, data<T> const& data, bool end=false) :
            text(text),
            const_data(data),
            current_node(data.root_node()) {
        if (end) {
            text_position = text.size();
        }
    }

    bool done() const {
        return(text_position == text.size() && current_dict_match == nullptr);
    }

    bool operator==(match_state<T> const& rhs) const {
        // verify that this is the same trie
        if (&const_data != &rhs.const_data) { return false; }
        // verify that this is the same search
        if (&text != &rhs.text) { return false; }
        // verify that we are at the same position
        if (text_position != rhs.text_position) { return false; }
        if (current_dict_match != rhs.current_dict_match) { return false; }
        if (current_word_index != rhs.current_word_index) { return false; }
        return true;
    }

    bool operator!=(match_state<T> const& rhs) const {
        return !(*this == rhs);
    }

    bool next() {
        if (current_dict_match != nullptr) {
            current_word_index = current_dict_match->word_index;
            current_dict_match = current_dict_match->dict_suffix_link;
            return true;
        }

        while (text_position < text.size()) {
            auto current_char = text[text_position];
            text_position++;

            while(true) {
                auto it = current_node->children.find(current_char);
                // if we can continue following the trie, do
                if (it != current_node->children.end()) {
                    current_node = &it->second;
                    break;
                }

                // if we are at the root, well this character just isn't here
                if (current_node == const_data.root_node()) {
                    break;
                }

                // this path failed, maybe a suffix will match
                current_node = current_node->suffix_link;
            }

            if (current_node->word_index > 0) {
                current_word_index = current_node->word_index;
                current_dict_match = current_node->dict_suffix_link;
                return true;
            }

            if (current_node->dict_suffix_link != nullptr) {
                current_dict_match = current_node->dict_suffix_link;
                current_word_index = current_dict_match->word_index;
                current_dict_match = current_dict_match->dict_suffix_link;
                return true;
            }
        }
        current_word_index = 0;
        return false;
    }

    T const& current() const {
        return const_data.get(current_word_index);
    }

private:

    const T& text;
    TSize text_position = 0;
    const data<T>& const_data;
    const node<TValue>* current_node;
    const node<TValue>* current_dict_match = nullptr;
    int current_word_index = 0;
};

template <class T>
static match_state<T> match_begin(T const& text, data<T> const& data) {
    return match_state<T>(text,data);
}

template <class T>
static match_state<T> match_end(T const& text, data<T> const& data) {
    return match_state<T>(text,data,true);
}

} // namespace internal
} // namespace corsicana

#endif //CORSICANA_INTERNAL_MATCH_STATE_HPP
