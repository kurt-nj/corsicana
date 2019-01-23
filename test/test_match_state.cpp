#include "catch.hpp"
#include "corsicana/internal/match_state.hpp"
#include <iostream>

TEST_CASE("Match State Equality", "[match_state.equals]") {

    corsicana::data<std::string> mydata;
    std::string text = "HELLO WORLD";

    SECTION("done") {
        auto state = corsicana::match_end(text,mydata);
        REQUIRE(state.done());
    }
    SECTION("end equals") {
        auto state1 = corsicana::match_end(text,mydata);
        auto state2 = corsicana::match_end(text,mydata);
        REQUIRE(state1 == state2);
    }
    SECTION("begin equals") {
        auto state1 = corsicana::match_begin(text,mydata);
        auto state2 = corsicana::match_begin(text,mydata);
        REQUIRE(state1 == state2);
    }
    SECTION("not equals") {
        auto state1 = corsicana::match_begin(text,mydata);
        auto state2 = corsicana::match_end(text,mydata);
        REQUIRE(state1 != state2);
    }
}

TEST_CASE("Match State Next", "[match_state.next]") {

}
