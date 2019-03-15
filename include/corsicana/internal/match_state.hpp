#ifndef CORSICANA_INTERNAL_MATCH_STATE_HPP
#define CORSICANA_INTERNAL_MATCH_STATE_HPP

#include "corsicana/internal/data.hpp"
#include "corsicana/internal/node.hpp"

namespace corsicana {
namespace internal {

// Internal class that performs the Aho-Corasick algorithm and stores the current state information
// API subject to change. Not intended for general usage.
template <class T>
class match_state {
public:

    using TValue = typename T::value_type;
    using TSize = typename T::size_type;

    match_state(T const& text_in, data<T> const& data, bool end=false) :
            text(&text_in),
            const_data(&data),
            current_node(data.root_node()) {
        if (end) {
            text_position = text->size();
        }
    }
    match_state(match_state<T> const&) = default;
    match_state(match_state<T>&&) noexcept = default;
    match_state<T>& operator=(match_state<T> const&) = default;
    match_state<T>& operator=(match_state<T>&&) noexcept = default;

    // Returns true if search position is at the final spot
    bool done() const {
        return(text_position == text->size() && current_dict_match == nullptr);
    }

    bool operator==(match_state<T> const& rhs) const {
        // verify that this is the same trie
        if (const_data != rhs.const_data) { return false; }
        // verify that this is the same search
        if (text != rhs.text) { return false; }
        // verify that we are at the same position
        if (text_position != rhs.text_position) { return false; }
        if (current_dict_match != rhs.current_dict_match) { return false; }
        if (current_word != rhs.current_word) { return false; }
        return true;
    }

    bool operator!=(match_state<T> const& rhs) const {
        return !(*this == rhs);
    }

    // Go to the next match if any.
    // Returns true if a match is found, false if we reach the end
    bool next() {
        // start by looking at the dict suffix
        // we need to exhaust all of our suffix links before searching further
        if (current_dict_match != nullptr) {
            current_word = current_dict_match->word;
            current_dict_match = current_dict_match->dict_suffix_link;
            return true;
        }
        // continue from where we stopped last
        while (text_position < text->size()) {
            auto current_char = text->operator[](text_position);
            ++text_position;

            while(true) {
                auto it = current_node->children.find(current_char);
                // if we can continue following the trie, do
                if (it != current_node->children.end()) {
                    current_node = it->second.get();
                    break;
                }

                // if we are at the root, well this character just isn't here
                if (current_node == const_data->root_node()) {
                    break;
                }

                // this path failed, maybe a suffix will match
                current_node = current_node->suffix_link;
            }

            // if we hit the end of a word then stop there
            if (current_node->word) {
                current_word = current_node->word;
                current_dict_match = current_node->dict_suffix_link;
                return true;
            }

            // if we hit dict suffix to a shorter word, then stop there
            if (current_node->dict_suffix_link != nullptr) {
                current_dict_match = current_node->dict_suffix_link;
                current_word = current_dict_match->word;
                current_dict_match = current_dict_match->dict_suffix_link;
                return true;
            }
        }
        // nothing left
        current_word = nullptr;
        return false;
    }

    // Get the current word pointed at by the current match
    T const& current() const {
        return *current_word;
    }

private:

    const T* text;
    TSize text_position = 0;
    const data<T>* const_data;
    const node<T>* current_node;
    const node<T>* current_dict_match = nullptr;
    const T* current_word = nullptr;
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
