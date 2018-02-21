#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "data.hpp"
#include "doctest.h"

using fun::data::fmap;
using fun::data::join;
using fun::data::map;
using fun::data::maybe;

SCENARIO("fun::data::array")
{

    GIVEN("a valid maybe<int>")
    {
        constexpr auto data = maybe{ 1 };
        WHEN("fmapping over it")
        {
            constexpr auto result = fmap([](auto x) { return x * 2; })(data);
            THEN("it should yield a valid result")
            {
                CHECK(result);
                CHECK(result.value == 2);
            }
        }
    }

    GIVEN("a nested maybe<maybe<int>>")
    {
        constexpr maybe<maybe<int>> data = maybe{ maybe{ 1 } };
        WHEN("joining it")
        {
            constexpr auto result = join(data);
            THEN("the inner maybe<int> should be returned")
            {
                CHECK(result.valid);
                CHECK(result.value == 1);
            }
        }
    }

    GIVEN("a valid maybe<int>")
    {
        constexpr auto one = maybe{ 1 };

        WHEN("chaining successful computations")
        {
            auto f = [](auto x) {
                return maybe{ 2 * x };
            };

            auto g = [](auto x) {
                return maybe{ 4 * x };
            };

            auto computation = bind(one)([f, g](auto x) {
                return bind(f(x))([f, g](auto&& x) {
                    return bind(g(x))([f, g](auto&& x) {
                        return maybe{ x };
                    });
                });
            });

            THEN("the correct value should be returned")
            {
                CHECK(computation);
                CHECK(computation.value == 8);
            }
        }
    }
}
