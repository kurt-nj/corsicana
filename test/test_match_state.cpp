#include "catch.hpp"
#include "corsicana/internal/match_state.hpp"
#include <iostream>

TEST_CASE("Match State Done", "[match_state.done]") {
    corsicana::internal::data<std::string> mydata;
    std::string text = "HELLO WORLD";

    SECTION("done") {
        auto state = corsicana::internal::match_end(text,mydata);
        REQUIRE(state.done());
    }
    SECTION("not done") {
        auto state = corsicana::internal::match_begin(text,mydata);
        REQUIRE(!state.done());
    }
}


TEST_CASE("Match State Equals", "[match_state.==]") {

    corsicana::internal::data<std::string> mydata;
    std::string text = "HELLO WORLD";

    SECTION("end equals") {
        auto state1 = corsicana::internal::match_end(text,mydata);
        auto state2 = corsicana::internal::match_end(text,mydata);
        REQUIRE(state1 == state2);
    }
    SECTION("begin equals") {
        auto state1 = corsicana::internal::match_begin(text,mydata);
        auto state2 = corsicana::internal::match_begin(text,mydata);
        REQUIRE(state1 == state2);
    }
    SECTION("not equals") {
        auto state1 = corsicana::internal::match_begin(text,mydata);
        auto state2 = corsicana::internal::match_end(text,mydata);
        REQUIRE(!(state1 == state2));
        REQUIRE(state1 != state2);
    }
}

TEST_CASE("Match State Copy", "[match_state.=") {
    corsicana::internal::data<std::string> mydata;
    std::string text = "HELLO WORLD";
    SECTION("copy constructor") {
        auto orig = corsicana::internal::match_begin(text,mydata);
        corsicana::internal::match_state<std::string> copy(orig);
        REQUIRE(copy == orig);
    }
    SECTION("copy assignment") {
        auto orig = corsicana::internal::match_begin(text,mydata);
        corsicana::internal::match_state<std::string> copy = orig;
        REQUIRE(copy == orig);
    }
}
