#ifndef CORSICANA_TRIE_HPP
#define CORSICANA_TRIE_HPP

#include <string>
#include "corsicana/basic_trie.hpp"

namespace corsicana {

using trie = basic_trie<std::string>;
using wtrie = basic_trie<std::wstring>;

} // namespace corsicana

#endif //CORSICANA_TRIE_HPP
