#include "catch.hpp"
#include "corsicana/trie.hpp"

using namespace Catch::Matchers;

TEST_CASE("Wide Trie", "[corsicana.wtrie]") {
    // War and Peace by Leo Tolstoy
    // "And the fete at the English ambassador's? Today is Wednesday."
    std::wstring pattern = L"А праздник английского посланника? Нынче середа.";

    corsicana::wtrie_builder wt_build;
    auto wt = wt_build.insert(L"английского").insert(L"середа").insert(L"приближенная").build();
    auto all = wt.match(pattern).all();
    std::vector<corsicana::wresult> expected = { {L"английского",11}, {L"середа",41} };
    REQUIRE_THAT(all, Equals(expected));
}

TEST_CASE("U16 Trie", "[corsicana.u16trie]") {
    // unattributed Armenian poem
    std::u16string pattern = u"Աեցեհի իմ լավ ?ւղիե լավարար,"
                             u"Կյաեբս չտայի կասկածի մհգիե..."
                             u"Այեպհս կ?ւզհի մհկե իեծ ?ավատր,"
                             u"Այեպհս կ?ւզհի ?ավատալ մհկիե։";
    corsicana::u16trie_builder u16t_build;
    auto u16t = u16t_build.insert(u"լավարար").insert(u"Այեպհս").insert(u"NOT ARMENIAN?").build();
    auto all = u16t.match(pattern).all();
    std::vector<corsicana::u16result> expected = { {u"լավարար",0}, {u"Այեպհս",10}, {u"Այեպհս",20} };
    REQUIRE_THAT(all, Equals(expected));
}

// Aho-Corasick is designed for text but it could be used for any sequential data
TEST_CASE("Custom Trie", "[corsicana.basic_trie<std::vector<long>>]") {
    corsicana::basic_trie_builder<std::vector<long>> ct_build;
    auto ct = ct_build
            .insert( { 111, 444, 555 } )
            .insert( { 1, 2, 3 } )
            .insert( { 9000 } )
            .insert( { 8888888 })
            .build();
    std::vector<long> pattern = { 9000, 1, 2, 3, 0, 9000, 9, 9001 };
    std::vector<corsicana::basic_result<std::vector<long>>> expected = { {{ 9000 },0}, {{ 1, 2, 3 },1}, {{ 9000 },5} };
    auto all = ct.match(pattern).all();
    REQUIRE_THAT(all, Equals(expected));
}
