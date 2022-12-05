#pragma once

#include <type_traits>

namespace kdalgorithms {
namespace traits {

    template <typename... Ts>
    struct make_void
    {
        typedef void type;
    };

    template <typename... Ts>
    using void_t = typename make_void<Ts...>::type;

    template <typename T, typename S = void_t<>>
    struct has_reserve_method : std::false_type
    {
    };

    template <typename T>
    struct has_reserve_method<T, void_t<decltype(std::declval<T>().reserve(42))>> : std::true_type
    {
    };

    template <typename T>
    constexpr bool has_reserve_method_v = has_reserve_method<T>::value;

} // namespace traits
} // namespace kdalgorithms
