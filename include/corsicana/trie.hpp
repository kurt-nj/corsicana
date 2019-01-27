#ifndef CORSICANA_TRIE_HPP
#define CORSICANA_TRIE_HPP

#include <string>
#include "corsicana/basic_trie_builder.hpp"
#include "corsicana/basic_trie.hpp"

namespace corsicana {

// The main include for the Corsicana Aho-Corasick library.
// This file declares some basic template instantiations for the standard strings.
// Custom instantiations can also be created.
// See the README for more details on how to use this library.

using trie_builder = basic_trie_builder<std::string>;
using trie = basic_trie<std::string>;

using wtrie_builder = basic_trie_builder<std::wstring>;
using wtrie = basic_trie<std::wstring>;

using u16trie_builder = basic_trie_builder<std::u16string>;
using u16trie = basic_trie<std::u16string>;

using u32trie_builder = basic_trie_builder<std::u32string>;
using u32trie = basic_trie<std::u32string>;

} // namespace corsicana

#endif //CORSICANA_TRIE_HPP
