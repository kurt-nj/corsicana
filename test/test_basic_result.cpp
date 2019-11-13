#include "catch.hpp"
#include "corsicana/basic_result.hpp"

TEST_CASE("Result Equals", "[basic_result.==]") {
    corsicana::basic_result<std::string> r1 { "example", 9000 };
    corsicana::basic_result<std::string> r2 { "example", 9000 };
    REQUIRE(r1 == r2);
    REQUIRE(r2 == r1);
}

TEST_CASE("Result Not Equals", "[basic_result.!=]") {
    corsicana::basic_result<std::string> r1 { "example", 9000 };
    corsicana::basic_result<std::string> r2 { "example", 9001 };
    REQUIRE(r1 != r2);
    REQUIRE(r2 != r1);
}