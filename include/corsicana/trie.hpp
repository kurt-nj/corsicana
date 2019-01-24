#ifndef CORSICANA_TRIE_HPP
#define CORSICANA_TRIE_HPP

#include <string>
#include "corsicana/basic_trie.hpp"

namespace corsicana {

using trie = basic_trie<std::string>;
using wtrie = basic_trie<std::wstring>;
using u16trie = basic_trie<std::u16string>;
using u32trie = basic_trie<std::u32string>;

} // namespace corsicana

#endif //CORSICANA_TRIE_HPP
