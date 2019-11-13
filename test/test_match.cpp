#include "catch.hpp"
#include <iostream>
#include <utility>

#include "corsicana/trie.hpp"
#include "corsicana/result_io.hpp"

using namespace Catch::Matchers;

TEST_CASE("Match All", "[corsicana.match.all]") {
    corsicana::trie_builder tbuild;
    auto t = tbuild.insert("hers").insert("his").insert("she").insert("he").build();
    SECTION("matches") {
        std::vector<corsicana::result> expected = { {"she",1}, {"he",2}, {"hers",2} };
        auto all = t.match("ushers").all();
        REQUIRE_THAT(all, Equals(expected));
    }
    SECTION("no matches") {
        auto all = t.match("santamaria").all();
        REQUIRE(all.empty());
    }
}

TEST_CASE("Match Count", "[corsicana.match.count]") {
    corsicana::trie_builder tbuild;
    auto t = tbuild.insert("hers").insert("his").insert("she").insert("he").build();
    SECTION("matches") {
        REQUIRE(t.match("ushers").count() == 3);
    }
    SECTION("no matches") {
        REQUIRE(t.match("santamaria").count() == 0);
    }
}

TEST_CASE("Match Any", "[corsicana.match.any]") {
    corsicana::trie_builder tbuild;
    auto t = tbuild.insert("hers").insert("his").insert("she").insert("he").build();
    SECTION("matches") {
        REQUIRE(t.match("ushers").any());
    }
    SECTION("no matches") {
        REQUIRE(!t.match("santamaria").any());
    }
}

TEST_CASE("Match Iterator", "[corsicana.match.iterator]") {
    corsicana::trie_builder tbuild;
    auto t = tbuild.insert("hers").insert("his").insert("she").insert("he").build();
    SECTION("matches") {
        std::vector<corsicana::result> expected = { {"she",1}, {"he",2}, {"hers",2} };
        auto match = t.match("ushers");
        std::vector<corsicana::result> actual(match.begin(), match.end());
        REQUIRE_THAT(actual, Equals(expected));
    }
    SECTION("matches - std methods") {
        std::vector<corsicana::result> expected = { {"she",1}, {"he",2}, {"hers",2} };
        auto match = t.match("ushers");
        std::vector<corsicana::result> actual(std::begin(match), std::end(match));
        REQUIRE_THAT(actual, Equals(expected));
    }
    SECTION("no matches") {
        auto match = t.match("santamaria");
        REQUIRE(match.begin() == match.end());
    }
    SECTION("iterator dereference") {
        auto match = t.match("ushers");
        auto it = match.begin();
        REQUIRE(*it == corsicana::result{"she",1});
        REQUIRE(it->match.compare("she") == 0);
    }
    SECTION("iterator copy") {
        auto match = t.match("ushers");
        auto it = match.begin();
        corsicana::match<std::string>::iterator copy = it;
        REQUIRE(it == copy);
    }
    SECTION("iterator copy assignment") {
        auto match = t.match("ushers");
        auto it = match.begin();
        corsicana::match<std::string>::iterator copy(it);
        REQUIRE(it == copy);
    }
    SECTION("iterator is swappable") {
        REQUIRE(std::is_move_assignable<corsicana::match<std::string>::iterator>::value);
        auto match = t.match("ushers");
        auto it1 = match.begin();
        auto it2 = match.end();
        std::swap(it1, it2);
        REQUIRE(it1 == match.end());
        REQUIRE(it2 == match.begin());
    }
}

// Test specifically for heavy overlap
TEST_CASE("Match Overlap") {
    corsicana::trie_builder tbuild;
    auto t = tbuild.insert("he").insert("hehehehe").build();
    std::vector<corsicana::result> expected = { {"he",0}, {"he",2}, {"he",4}, {"hehehehe",0}, {"he",6}, {"hehehehe",2}, {"he",8} };
    REQUIRE_THAT(t.match("hehehehehe").all(), Equals(expected));
}
