#include "RegExp.h"

#include "catch.hpp"

TEST_CASE("constructs regexes", "[RegExp]") {
    RegExp r1("");
    RegExp r2(".*");
    RegExp r3("\"eventId\":([0-9]+)");

    SECTION("throws on bad") {
        bool threw = false;
        try {
            RegExp r("(");
        } catch (const std::runtime_error &e) {
            threw = true;
            REQUIRE(e.what() == std::string("Unmatched ( or \\("));  // this is probably a bridge too far
        }
        REQUIRE(threw);
    }
}

namespace {
std::string S(const char *s, RegExp::Match match) {
    return std::string(s + match.first, match.second - match.first);
}
}

TEST_CASE("matches", "[RegExp]") {
    RegExp r("\"eventId\":([0-9]+)");
    RegExp::Matches matches;
    REQUIRE(r.exec("not a match", matches) == false);
    char const *against = "\"eventId\":123234,moose";
    REQUIRE(r.exec(against, matches) == true);
    REQUIRE(matches.size() == 2);
    REQUIRE(S(against, matches[0]) == "\"eventId\":123234");
    REQUIRE(S(against, matches[1]) == "123234");
}