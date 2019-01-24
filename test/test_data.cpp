#include "catch.hpp"
#include "corsicana/internal/data.hpp"
#include <iostream>


TEST_CASE("Data Insert", "[corsicana.internal.data.insert]") {
    SECTION("insert data") {
        corsicana::internal::data<std::string> data;
        std::string str("hello world");
        data.insert(str);
        REQUIRE(data.get(1) == str);
    }
}

TEST_CASE("Data Root Node", "[corsicana.internal.data.root_node]") {
    SECTION("Not Null") {
        corsicana::internal::data<std::string> data;
        REQUIRE(data.root_node() != nullptr);
    }
}
