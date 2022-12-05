#pragma once

#include <type_traits>
#include <utility>
#if __cplusplus >= 202002L
#include <concepts>
#endif

namespace kdalgorithms {
// FIXME remove before release - for now I'm fed up with retyping this over and over again :)
template <typename T>
struct print_type;

// ----- helper functions for older C++ versions -----
#if __cplusplus >= 202002L
template <typename T>
using remove_cvref_t = std::remove_cvref_t<T>;
#else
template <typename T>
using remove_cvref_t = typename std::remove_const<typename std::remove_reference<T>::type>::type;
#endif

// -------------------- general helpers --------------------
template <typename Container>
using ValueType = typename remove_cvref_t<Container>::value_type;

// -------------------- concepts --------------------
#if __cplusplus >= 202002L
template <typename Container, typename Value>
concept ContainerOfType = std::convertible_to<Value, ValueType<Container>>;

template <typename UnaryPredicate, typename Container>
concept UnaryPredicateOnContainerValues =
    std::is_invocable_r_v<bool, UnaryPredicate, ValueType<Container>>;

template <typename BinaryPredicate, typename Container>
concept BinaryPredicateOnContainerValues =
    std::is_invocable_r_v<bool, BinaryPredicate, ValueType<Container>, ValueType<Container>>;

#endif

} // namespace kdalgorithms
