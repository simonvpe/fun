#include "array.hpp"

namespace fun::data {

constexpr auto map(auto &&f) {
  return [=](Functor &&a) -> Functor { return a.map(f); };
}

constexpr auto apply(Applicative &&f) -> Applicative {
  return [=](Applicative &&a) -> Applicative { return a.apply(f); };
}

} // namespace fun::data
