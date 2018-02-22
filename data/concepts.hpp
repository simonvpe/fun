#pragma once

namespace fun::data {

constexpr auto monoid = [](auto x) { return x; };

template <typename T, typename A, typename B>
concept bool Monoid = requires(T t)
{
    t(A{})->B;
};

template <typename T>
concept bool Functor = requires(T t)
{
    // fmap :: (a -> b) -> f a -> f b
    // (<$) :: Functor f => a -> f b -> f a
    t.map(monoid);
};

template <typename T>
concept bool Applicative = Functor<T>&& requires(T t)
{
    // IS ALSO A FUNCTOR
    //
    // pure :: a -> f a
    //
    // (<*>) :: f (a -> b) -> f a -> f b (apply)
    // OR
    // liftA2 :: (a -> b -> c) -> f a -> f b -> f c
    t.apply(T{ monoid });
};

template <typename T>
concept bool Monad = requires(T t)
{
    // IS ALSO AN APPLICATIVE
    // (>>=) :: forall a b. m a -> (a -> m b) -> m b (bind)
    true;
};

template <typename T>
concept bool is_lfoldable = requires(T t)
{
    {
        t.lfold(int{}, monoid)
    }
    ->int;
};

} // namespace fun::data
