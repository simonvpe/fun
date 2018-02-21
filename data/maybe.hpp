#pragma once

#include "concepts.hpp"

namespace fun::data {

template <typename T>
class maybe {
public:
    using value_type = T;

    constexpr maybe()
        : valid{ false }
        , value{}
    {
    }

    constexpr maybe(const T& value)
        : valid{ true }
        , value{ value }
    {
    }

    constexpr auto id() const
    {
        return maybe<T>{ *this };
    }

    constexpr maybe<T> map(auto&& f) const
    {
        if (valid)
            return { value.map(f) };
        return {};
    }

    constexpr auto apply(maybe<auto> f) const
    {
        if (valid && f)
            return maybe{ f.value(value) };
        return maybe{ decltype(f.value(value)){} };
    }

    constexpr auto bind(auto&& f) const
    {
        using B = decltype(f(value));
        if (valid)
            return B{ f(value) };
        return B{};
    }

    explicit constexpr operator bool() const { return valid; }

    const T value;
    const bool valid;
};

} // namespace fun::data
