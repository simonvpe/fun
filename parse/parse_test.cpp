#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <data.hpp>

using fun::data::make_array;
using fun::data::maybe;

SCENARIO("Maybe based parser")
{
    // pchar :: Char -> Stream -> Maybe Stream
    constexpr auto pchar = [](char c) {
        return [=](auto stream) {
            return maybe{ stream }.bind([=](auto s) -> maybe<decltype(s.tail())> {
                if (s.head() == c)
                    return maybe{ s.tail() };
                return {};
            });
        };
    };

    constexpr auto parsek = pchar('k');
    CHECK(parsek(make_array('k', 'b', 'c')));
}
