#ifndef CORSICANA_BASIC_RESULT_HPP
#define CORSICANA_BASIC_RESULT_HPP

namespace corsicana {

template <class T>
struct basic_result {

    using TSize = typename T::size_type;

    /// Default constructor
    basic_result() = default;
    /// constructor with values
    basic_result(T const& value, TSize position) : match(value), match_position(position) {}

    T match;
    TSize match_position = 0;

    bool operator==(basic_result<T> const& rhs) const {
        if (match != rhs.match) { return false; }
        if (match_position != rhs.match_position) { return false; }
        return true;
    }

    bool operator!=(basic_result<T> const& rhs) const {
        return !(*this == rhs);
    }
};

} // namespace corsicana

#endif // CORSICANA_BASIC_RESULT_HPP