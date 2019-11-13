#ifndef CORSICANA_BASIC_RESULT_HPP
#define CORSICANA_BASIC_RESULT_HPP

namespace corsicana {

/// Matched search result.
/// Gives a matched substring and its starting position in the searched text
template <class T>
struct basic_result {

    using TSize = typename T::size_type;

    basic_result() = default;
    basic_result(T const& value, TSize position) : match(value), match_position(position) {}

    // a matched substring
    T match;
    // the start position of the matched substring in the given search text
    TSize match_position = 0;

    bool operator==(basic_result<T> const& rhs) const {
        if (match_position != rhs.match_position) { return false; }
        if (match != rhs.match) { return false; }
        return true;
    }

    bool operator!=(basic_result<T> const& rhs) const {
        return !(*this == rhs);
    }
};

} // namespace corsicana

#endif // CORSICANA_BASIC_RESULT_HPP