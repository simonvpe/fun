#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "data.hpp"
#include "doctest.h"

using fun::data::array;
using fun::data::make_array;
using fun::data::map;

SCENARIO("fun::data::array") {

  GIVEN("an array created with make_array") {
    constexpr auto data = make_array(1, 2, 3);
    THEN("it should be correct") { CHECK(data[0] == 1); }
    THEN("it should be correct") { CHECK(data[2] == 3); }
  }

  GIVEN("two arrays created with make_array") {
    constexpr auto left = make_array(1, 2, 3);
    constexpr auto right = make_array(4, 5, 6, 7);
    WHEN("adding the arrays together") {
      constexpr auto result = left + right;
      THEN("the first value should be correct") { CHECK(result[0] == 1); }
      THEN("the middle value should be correct") { CHECK(result[3] == 4); }
      THEN("the last value should be correct") { CHECK(result[6] == 7); }
    }
  }

  GIVEN("an array created with make_array") {
    constexpr auto data = make_array(1, 2, 3);
    WHEN("mapping a function over the array") {
      constexpr auto fdouble = map([](auto x) { return 2 * x; });
      constexpr auto result = fdouble(data);
      THEN("the first value should be correct") { CHECK(result[0] == 2); }
      THEN("the last value should be correct") { CHECK(result[2] == 6); }
    }
  }

  GIVEN("an array created with make_array") {
    constexpr auto data = make_array(1, 2, 3);
    WHEN("mapping a function over the array") {
      constexpr auto ftriplet =
          map([](auto x) { return make_array(x, x + 1, x + 2); });
      constexpr auto result = ftriplet(data);
      THEN("the first value should be correct") {
        CHECK(result[0][0] == 1);
        CHECK(result[0][1] == 2);
        CHECK(result[0][2] == 3);
      }
      THEN("the last value should be correct") {
        CHECK(result[2][0] == 3);
        CHECK(result[2][1] == 4);
        CHECK(result[2][2] == 5);
      }
    }
  }
}
