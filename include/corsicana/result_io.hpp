#ifndef CORSICANA_RESULT_IO_HPP
#define CORSICANA_RESULT_IO_HPP

#include <ostream>
#include "corsicana/basic_result.hpp"

namespace corsicana {

/// Helper streaming operator for printing results
/// Assumes that the trie type has stream operator available
template <class CharType, class CharTrait, class T>
std::basic_ostream<CharType, CharTrait>&
operator<<(std::basic_ostream<CharType, CharTrait>& out, basic_result<T> const& result) {
    out << result.match << ":" << result.match_position;
    return out;
}

} // namespace corsicana

#endif // CORSICANA_RESULT_IO_HPP