#include <errors_cpp11/try.hpp>

#include <string>

#include <catch2/catch.hpp>

TEST_CASE("ERRORS_TRY with expected")
{
    auto f = [&](int n) -> errors::expected<int, std::string> { 
        if(n > 0) {
            return n;
        }
        return errors::make_unexpected("less than zero");
    };
    auto g = [&](int n) -> errors::expected<std::string, std::string> {
        ERRORS_TRY(auto m, f(n*2));
        return std::to_string(m);
    };
    REQUIRE(g(1) == "2");
    REQUIRE(g(-1).error() == "less than zero");
}

TEST_CASE("ERRORS_TRY with optional")
{
    auto f = [&](int n) -> errors::optional<int> {
        if(n > 0) {
            return n;
        }
        return errors::nullopt;
    };
    auto g = [&](int n) -> errors::optional<std::string> {
        ERRORS_TRY(auto m, f(n*2));
        return std::to_string(m);
    };
    REQUIRE(g(1) == "2");
    REQUIRE(g(-1) == errors::nullopt);
}
