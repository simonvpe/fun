#pragma once

#include "concepts.hpp"

namespace fun::data {

enum class Variant {
    Left,
    Right
};

template <typename E>
struct left {
    const E value;
};

template <typename A>
struct right {
    const A value;
};

template <typename E, typename A>
class either {
public:
    using left_type = E;
    using right_type = A;

    constexpr either(const left<E>& v)
        : payload{ left : v.value }
        , variant{ Variant::Left }
    {
    }

    constexpr either(const right<A>& v)
        : payload{ right : v.value }
        , variant{ Variant::Right }
    {
    }

    constexpr auto apply(either<E, auto> f) const
    {
        using B = decltype(f.payload.right(payload.right));
        if (variant == Variant::Right && f.variant == Variant::Right)
            return either{ f.payload.right(payload.right), Variant::Right };
        if (variant == Variant::Right && f.variant == Variant::Left)
            return either{ f.payload.left, Variant::Left };
        return either{ payload.left, Variant::Left };
    }

    constexpr auto bind(auto&& f) const -> either<E, auto>
    {
        using B = typename decltype(f(payload.right))::right_type;
        if (variant == Variant::Right) {
            return f(payload.right);
        } else {
            return either<E, B>{ left<E>{ payload.left } };
        }
    }

    const union Payload {
        const E left;
        const A right;
    } payload;
    const Variant variant;
};

constexpr auto get_right(const either<auto, auto>& e)
{
    return e.variant == Variant::Right
        ? e.payload.right
        : throw std::runtime_error("Accessing invalid variant");
}

constexpr auto get_left(const either<auto, auto>& e)
{
    return e.variant == Variant::Left
        ? e.payload.left
        : throw std::runtime_error("Accessing invalid variant");
}

constexpr bool is_left(const either<auto, auto>& e) { return e.variant == Variant::Left; }

constexpr bool is_right(const either<auto, auto>& e) { return e.variant == Variant::Right; }

} // namespace fun::data
