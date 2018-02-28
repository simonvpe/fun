#include "array.hpp"
#include "either.hpp"
#include "maybe.hpp"

namespace fun::data {

constexpr auto map(auto&& f)
{
    return [=](Functor&& a) -> Functor { return a.map(f); };
}

constexpr auto apply(Applicative&& f) -> Applicative
{
    return [=](Applicative&& a) -> Applicative { return a.apply(f); };
}

// bind :: M a -> (a -> M b) -> M b
constexpr auto bind(Monad&& a)
{
    return [=](auto&& f) {
        return a.bind(f);
    };
}

// id :: M a -> M a
constexpr auto id = [](auto&& a) -> decltype(a) {
    return a;
};

// fmap :: (a -> b) -> (M a -> M b)
constexpr auto fmap(auto&& f)
{
    return [=](Monad&& a) {
        return bind(a)([=](auto x) { return decltype(a){ f(x) }; });
    };
};

// join :: M (M a) -> M a
constexpr auto join(Monad&& a)
{
    return bind(a)([=](auto x) { return id(x); });
}

} // namespace fun::data
