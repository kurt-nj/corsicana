#include "catch.hpp"
#include "corsicana/trie.hpp"
#include <iostream>


TEST_CASE("Search All on Trie", "[trie.search.all]") {
    SECTION("no match test") {
        corsicana::trie t;
        t.insert("five")
         .insert("nine")
         .insert("eleven")
         .freeze();
        auto match = t.match("four score and seven years ago");
        REQUIRE(match.all().size() == 0);
        REQUIRE(match.count() == 0);
    }
    SECTION("ushers test") {
        corsicana::trie t;
        t.insert("hers")
         .insert("his")
         .insert("she")
         .insert("he")
         .freeze();

        SECTION("all") {
            auto all = t.match("ushers").all();
            REQUIRE(all.size() == 3);
            REQUIRE(all[0] == "she");
            REQUIRE(all[1] == "he");
            REQUIRE(all[2] == "hers");
        }
        SECTION("count") {
            REQUIRE(t.match("ushers").count() == 3);
        }
        SECTION("iterator") {
            auto match = t.match("ushers");
            std::vector<std::string> all(match.begin(), match.end());
            REQUIRE(all.size() == 3);
            REQUIRE(all[0] == "she");
            REQUIRE(all[1] == "he");
            REQUIRE(all[2] == "hers");
        }
    }
    SECTION("overlap test") {
        corsicana::trie t;
        t.insert("he");
        t.insert("hehehehe");
        t.freeze();

        auto match = t.match("hehehehehe");
        auto all = match.all();
        REQUIRE(all.size() == 7);
        REQUIRE(match.count() == 7);
        REQUIRE(all[0] == "he");
        REQUIRE(all[1] == "he");
        REQUIRE(all[2] == "he");
        REQUIRE(all[3] == "hehehehe");
        REQUIRE(all[4] == "he");
        REQUIRE(all[5] == "hehehehe");
        REQUIRE(all[6] == "he");
    }
}
