#include "catch.hpp"
#include "corsicana/trie.hpp"

TEST_CASE("Builder Construcion", "[corsicana.basic_trie_builder]") {
    SECTION("default") {
        corsicana::trie_builder tbuild;
        tbuild.insert("hers").insert("his").insert("she").insert("he");
        REQUIRE(tbuild.build().match("ushers").count() == 3);
    }
    SECTION("iterator") {
        std::vector<std::string> input = { "hers", "his", "she", "he" };
        corsicana::trie_builder tbuild(input.begin(), input.end());
        REQUIRE(tbuild.build().match("ushers").count() == 3);
    }
    SECTION("initialization list") {
        corsicana::trie_builder tbuild = { "hers", "his", "she", "he" };
        REQUIRE(tbuild.build().match("ushers").count() == 3);
    }
}

TEST_CASE("Builder Insert", "[corsicana.basic_trie_builder.insert]") {
    SECTION("iterator insert") {
        std::vector<std::string> input = { "hers", "his", "she", "he" };
        corsicana::trie_builder tbuild;
        tbuild.insert(input.begin(), input.end());
        REQUIRE(tbuild.build().match("ushers").count() == 3);
    }
}