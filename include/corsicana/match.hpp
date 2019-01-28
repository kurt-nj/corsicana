#ifndef CORSICANA_MATCH_HPP
#define CORSICANA_MATCH_HPP

#include "corsicana/internal/match_state.hpp"
#include "corsicana/internal/data.hpp"

namespace corsicana {

// forward declaration
template <class T>
class basic_trie;

/// Class representing a single Aho-Corasick search.
/// The Aho-Corasick search can be run multiple times on one match object
/// but results are not saved off internally between queries.
template <class T>
class match {
public:

    friend class basic_trie<T>;

    /// Iterator implementation for matching
    /// Implemented as a one-way input iterator
    class iterator : public std::iterator<std::input_iterator_tag, T>
    {
        public:
            friend class corsicana::match<T>;

            iterator(iterator const&) = default;
            iterator(iterator&&) noexcept = default;
            iterator& operator=(iterator const&) = default;
            iterator& operator=(iterator&&) noexcept = default;

            iterator& operator++() {
                state.next();
                return *this;
            }
            iterator operator++(int) {
                iterator tmp(*this);
                operator++();
                return tmp;
            }

            T const& operator*() const { return state.current(); }
            const T* operator->() const { return &state.current(); }
            bool operator==(iterator const& rhs) const { return state == rhs.state; }
            bool operator!=(iterator const& rhs) const { return state != rhs.state; }
        private:
            explicit iterator(corsicana::internal::match_state<T> state_in) : state(state_in) {}
            corsicana::internal::match_state<T> state;
    };

    /// Returns the total total number of matches.
    int count() const {
        int count = 0;
        auto state = corsicana::internal::match_begin(text, const_data);
        while(state.next()) { ++count; }
        return count;
    }

    /// Returns true if there is any match.
    /// Will return after finding the first match and might not need to perform the full search
    bool any() const {
        auto state = corsicana::internal::match_begin(text, const_data);
        return state.next();
    }

    /// Returns a vector of all matches.
    std::vector<T> all() const {
        std::vector<T> output;
        auto state = corsicana::internal::match_begin(text, const_data);
        while(state.next()) {
            output.push_back(state.current());
        }
        return output;
    }

    /// Returns an iterator pointing to the first match.
    iterator begin() const {
        auto state = corsicana::internal::match_begin(text, const_data);
        // the begin iterator needs to already be pointing to the first element
        state.next();
        return match<T>::iterator(state);
    }

    /// Returns an iterator representing the search end.
    iterator end() const {
        auto state = corsicana::internal::match_end(text, const_data);
        return match<T>::iterator(state);
    }

private:
    match(T const& text_in, const corsicana::internal::data<T>& data) :
        text(text_in),
        const_data(data) {}

    T text;
    const corsicana::internal::data<T>& const_data;
};

} // namespace corsicana

#endif // CORSICANA_MATCH_HPP
