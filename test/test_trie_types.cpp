#include "catch.hpp"
#include "corsicana/trie.hpp"
#include <iostream>

using namespace Catch::Matchers;

TEST_CASE("Wide Trie", "[corsicana.wtrie]") {
    // War and Peace by Leo Tolstoy
    // "And the fete at the English ambassador's? Today is Wednesday."
    std::wstring pattern = L"А праздник английского посланника? Нынче середа.";

    corsicana::wtrie wt;
    wt.insert(L"английского").insert(L"середа").insert(L"приближенная").freeze();
    auto all = wt.match(pattern).all();
    std::vector<std::wstring> expected = { L"английского", L"середа" };
    REQUIRE_THAT(all, Equals(expected));
}

TEST_CASE("U16 Trie", "[corsicana.u16trie]") {
    // unattributed Armenian poem
    std::u16string pattern = u"Աեցեհի իմ լավ ?ւղիե լավարար,"
                             u"Կյաեբս չտայի կասկածի մհգիե..."
                             u"Այեպհս կ?ւզհի մհկե իեծ ?ավատր,"
                             u"Այեպհս կ?ւզհի ?ավատալ մհկիե։";
    corsicana::u16trie u16t;
    u16t.insert(u"լավարար").insert(u"Այեպհս").insert(u"NOT ARMENIAN?").freeze();
    auto all = u16t.match(pattern).all();
    std::vector<std::u16string> expected = { u"լավարար", u"Այեպհս", u"Այեպհս" };
    REQUIRE_THAT(all, Equals(expected));
}

// Aho-Corasick is designed for text but it could be used for any sequential data
TEST_CASE("Custom Trie", "[corsicana.basic_trie<std::vector<long>>]") {
    corsicana::basic_trie<std::vector<long>> ct;
    ct.insert( { 111, 444, 555 } )
      .insert( { 1, 2, 3 } )
      .insert( { 9000 } )
      .insert( { 8888888 })
      .freeze();
    std::vector<long> pattern = { 9000, 1, 2, 3, 0, 9000, 9, 9001 };
    std::vector<std::vector<long>> expected = { { 9000 }, { 1, 2, 3 }, { 9000 } };
    auto all = ct.match(pattern).all();
    REQUIRE_THAT(all, Equals(expected));
}
