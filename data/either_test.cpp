#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "data.hpp"
#include "doctest.h"

using fun::data::either;
using fun::data::fmap;
using fun::data::get_left;
using fun::data::get_right;
using fun::data::left;
using fun::data::map;
using fun::data::right;

SCENARIO("fun::data::either")
{
    GIVEN("a left instantiated either")
    {
        constexpr auto e = either<int, int>{ left<int>{ 1 } };
        WHEN("calling is_left")
        {
            constexpr auto result = is_left(e);
            THEN("it should return true")
            {
                CHECK(result);
            }
        }

        WHEN("calling is_right")
        {
            constexpr auto result = is_right(e);
            THEN("it should return false")
            {
                CHECK(!result);
            }
        }

        WHEN("calling get_right")
        {
            THEN("it should throw")
            {
                CHECK_THROWS(get_right(e));
            }
        }

        WHEN("calling get_left")
        {
            constexpr auto value = get_left(e);
            THEN("it should return the left value")
            {
                CHECK(get_left(e) == 1);
            }
        }

        WHEN("calling bind returning an error")
        {
            constexpr auto result = e.bind([](int x) {
                return either<int, int>{ left<int>{ x * 2 } };
            });
            CHECK_THROWS(get_right(result));
            CHECK(get_left(result) == 1);
        }

        WHEN("calling bind returning a right")
        {
            constexpr auto result = e.bind([](int x) {
                return either<int, int>{ right<int>{ x * 2 } };
            });
            CHECK_THROWS(get_right(result));
            CHECK(get_left(result) == 1);
        }
    }

    GIVEN("a right instantiated either")
    {
        constexpr auto e = either<int, int>{ right<int>{ 5 } };
        WHEN("calling is_left")
        {
            constexpr auto result = is_left(e);
            THEN("it should return false")
            {
                CHECK(!result);
            }
        }

        WHEN("calling is_right")
        {
            constexpr auto result = is_right(e);
            THEN("it should return true")
            {
                CHECK(result);
            }
        }

        WHEN("calling get_right")
        {
            THEN("it should return the right value")
            {
                CHECK(get_right(e));
            }
        }

        WHEN("calling get_left")
        {
            THEN("it should throw")
            {
                CHECK_THROWS(get_left(e));
            }
        }

        WHEN("calling bind returning an error")
        {
            constexpr auto result = e.bind([](int x) {
                return either<int, int>{ left<int>{ x * 2 } };
            });
            CHECK_THROWS(get_right(result));
            CHECK(get_left(result) == 10);
        }

        WHEN("calling bind returning a right")
        {
            constexpr auto result = e.bind([](int x) {
                return either<int, int>{ right<int>{ x * 2 } };
            });
            CHECK_THROWS(get_left(result));
            CHECK(get_right(result) == 10);
        }
    }
}
