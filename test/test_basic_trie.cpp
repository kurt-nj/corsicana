#include "catch.hpp"
#include "corsicana/trie.hpp"

TEST_CASE("Basic Trie Construcors", "[corsicana.basic_trie]") {
    corsicana::trie_builder tbuild = { "one", "two", "three" };
    SECTION("move") {
        std::unique_ptr<corsicana::trie> tptr(new corsicana::trie(tbuild.build()));
        REQUIRE(tptr->match("I have two coconuts").any());
    }
}