#pragma once

namespace fun::data {

constexpr auto monoid = [](auto x) { return x; };

template <typename T, typename A, typename B>
concept bool Monoid = requires(T t) {
  t(A{})->B;
};

template <typename T> concept bool Functor = requires(T t) { t.map(monoid); };

template <typename T> concept bool Applicative = Functor<T> &&requires(T t) {
  t.apply(T{monoid});
};

} // namespace fun::data
