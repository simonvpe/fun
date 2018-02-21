#pragma once

#include "concepts.hpp"
#include <array>
#include <experimental/type_traits>

namespace fun::data {

template <typename T, int N>
class array final {
public:
    using value_type = T;
    static constexpr int size = N;

    constexpr array()
        : payload{}
    {
    }

    constexpr array(std::array<T, N> values)
        : payload(std::move(values))
    {
    }

    template <int S>
    constexpr auto operator+(const array<T, S>& other) const
    {
        auto r = std::array<T, N + S>{};
        auto dest = std::begin(r);
        for (auto& x : payload)
            *dest++ = x;
        for (auto& x : other.payload)
            *dest++ = x;
        return array<T, N + S>{ r };
    }

    constexpr auto head() const
    {
        if constexpr (N <= 0)
            throw std::runtime_error("Empty array");
        return payload[0];
    }

    constexpr auto tail() const
    {
        if constexpr (N <= 0) {
            throw std::runtime_error("Empty array");
        } else {
            auto r = std::array<T, N - 1>{};
            auto src = cbegin(payload);
            for (auto& x : r)
                x = *++src;
            return array<T, N - 1>{ r };
        }
    }

    constexpr auto map(auto&& f) const
    {
        using R = decltype(f(T{}));
        auto r = std::array<R, N>{};
        auto dest = std::begin(r);
        for (auto& x : payload)
            *dest++ = f(x);
        return array<R, N>{ r };
    }

    constexpr T operator[](int i) const { return payload[i]; }

private:
    // Payload cannot be const in order to be able to fmap nested
    // arrays for example. Therefore it is made private, and all
    // other array classes are friended. This works for now but will
    // probably fail later.
    template <typename U, int S>
    friend class array;
    std::array<T, N> payload;
};

namespace details {
    template <class>
    struct is_ref_wrapper : std::false_type {
    };
    template <class T>
    struct is_ref_wrapper<std::reference_wrapper<T>> : std::true_type {
    };

    template <class T>
    using not_ref_wrapper = std::experimental::negation<is_ref_wrapper<std::decay_t<T>>>;

    template <class D, class...>
    struct return_type_helper {
        using type = D;
    };
    template <class... Types>
    struct return_type_helper<void, Types...> : std::common_type<Types...> {
        static_assert(std::experimental::conjunction_v<not_ref_wrapper<Types>...>,
            "Types cannot contain reference_wrappers when D is void");
    };

    template <class D, class... Types>
    using return_type = array<typename return_type_helper<D, Types...>::type, sizeof...(Types)>;
} // namespace details

template <class D = void, class... Types>
constexpr details::return_type<D, Types...> make_array(Types&&... t)
{
    return { { std::forward<Types>(t)... } };
}

} // namespace fun::data
