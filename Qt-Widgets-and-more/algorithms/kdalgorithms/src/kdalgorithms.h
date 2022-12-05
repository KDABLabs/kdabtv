#pragma once

#include "bits/copy_or_move_iterators.h"
#include "bits/filter.h"
#include "bits/has_reserve_trait.h"
#include "bits/operators.h"
#include "bits/return_type_trait.h"
#include "bits/shared.h"
#include "bits/transform.h"
#include <algorithm>
#include <numeric>
#include <type_traits>
#include <utility>

#if __cplusplus >= 201703L
#include <optional>
#endif

namespace kdalgorithms {

// -------------------- copy --------------------
template <typename InputContainer, typename OutputContainer>
#if __cplusplus >= 202002L
requires ContainerOfType<OutputContainer, ValueType<InputContainer>>
#endif
void copy(InputContainer &&input, OutputContainer &output)
{
#if __cplusplus >= 201703L
    if constexpr (traits::has_reserve_method_v<OutputContainer>) {
        output.reserve(input.size() + output.size());
    }
#endif
    auto range = copy_or_move_iterators(std::forward<InputContainer>(input));
    std::copy(range.begin, range.end, std::back_inserter(output));
}

// -------------------- all_of / any_of / none_of --------------------
template <typename Container, typename UnaryPredicate>
bool any_of(const Container &container, UnaryPredicate &&predicate)
{
    return std::any_of(container.cbegin(), container.cend(),
                       std::forward<UnaryPredicate>(predicate));
}

template <typename Container, typename UnaryPredicate>
bool all_of(const Container &container, UnaryPredicate &&predicate)
{
    return std::all_of(container.cbegin(), container.cend(),
                       std::forward<UnaryPredicate>(predicate));
}

template <typename Container, typename UnaryPredicate>
bool none_of(const Container &container, UnaryPredicate &&predicate)
{
    return std::none_of(container.cbegin(), container.cend(),
                        std::forward<UnaryPredicate>(predicate));
}

// -------------------- reverse / reversed --------------------
template <typename Container>
void reverse(Container &container)
{
    std::reverse(container.begin(), container.end());
}

template <typename Container>
Container reversed(Container container)
{
    reverse(container);
    return container;
}

// -------------------- sort / sorted --------------------
template <typename Container, typename Compare = std::less<ValueType<Container>>>
void sort(Container &container, Compare &&compare = {})
{
    std::sort(container.begin(), container.end(), std::forward<Compare>(compare));
}

template <typename Container, typename Compare = std::less<ValueType<Container>>>
Container sorted(Container container, Compare &&compare = {})
{
    sort(container, std::forward<Compare>(compare));
    return container;
}

// -------------------- is_sorted --------------------
template <typename Container, typename Compare = std::less<ValueType<Container>>>
bool is_sorted(const Container &container, Compare &&compare = {})
{
    return std::is_sorted(container.cbegin(), container.cend(), std::forward<Compare>(compare));
}

// -------------------- contains / value_in --------------------
template <typename Container, typename Value>
#if __cplusplus >= 202002L
requires ContainerOfType<Container, Value>
#endif
bool contains(const Container &container, Value &&value)
{
    return std::find(container.cbegin(), container.cend(), std::forward<Value>(value))
        != std::end(container);
}

template <typename Value>
bool contains(std::initializer_list<Value> container, Value &&value)
{
    const auto it = std::find(container.begin(), container.end(), std::forward<Value>(value));
    return it != container.end();
}

template <typename Value>
bool value_in(Value &&value, std::initializer_list<Value> container)
{
    return contains(container, std::forward<Value>(value));
}

// -------------------- count / count_if --------------------
template <typename Container, typename Value>
#if __cplusplus >= 202002L
requires ContainerOfType<Container, Value>
#endif
int count(const Container &container, Value &&value)
{
    return std::count(container.cbegin(), container.cend(), std::forward<Value>(value));
}

template <typename Container, typename UnaryPredicate>
#if __cplusplus >= 202002L
requires UnaryPredicateOnContainerValues<UnaryPredicate, Container>
#endif
int count_if(const Container &container, UnaryPredicate &&predicate)
{
    return std::count_if(container.cbegin(), container.cend(),
                         std::forward<UnaryPredicate>(predicate));
}

// -------------------- min / max --------------------
#if __cplusplus >= 201703L
template <typename Container, typename Compare = std::less<ValueType<Container>>>
#if __cplusplus >= 202002L
requires BinaryPredicateOnContainerValues<Compare, Container>
#endif
    std::optional<ValueType<Container>> max_element(const Container &container,
                                                    Compare &&compare = {})
{
    if (container.empty())
        return {};
    return *std::max_element(container.cbegin(), container.cend(), std::forward<Compare>(compare));
}

template <typename Container, typename Compare = std::less<ValueType<Container>>>
#if __cplusplus >= 202002L
requires BinaryPredicateOnContainerValues<Compare, Container>
#endif
    std::optional<ValueType<Container>> min_element(const Container &container,
                                                    Compare &&compare = {})
{
    if (container.empty())
        return {};
    return *std::min_element(container.cbegin(), container.cend(), std::forward<Compare>(compare));
}
#endif

// -------------------- max_value_less_than / min_value_greater_than --------------------
#if __cplusplus >= 201703L
template <typename Container, typename Item, typename Compare = std::less<ValueType<Container>>>
#if __cplusplus >= 202002L
requires BinaryPredicateOnContainerValues<Compare, Container> && ContainerOfType<Container, Item>
#endif
    std::optional<Item> max_value_less_than(const Container &container, Item &&needle,
                                            Compare &&compare = {})
{
    auto it = std::lower_bound(container.cbegin(), container.cend(), std::forward<Item>(needle),
                               std::forward<Compare>(compare));

    if (it == container.cbegin())
        return {};
    --it;
    return *it;
}

template <typename Container, typename Item, typename Compare = std::less<ValueType<Container>>>
#if __cplusplus >= 202002L
requires BinaryPredicateOnContainerValues<Compare, Container> && ContainerOfType<Container, Item>
#endif
    std::optional<Item> min_value_greater_than(const Container &container, Item &&needle,
                                               Compare &&compare = {})
{
    auto it = std::upper_bound(container.cbegin(), container.cend(), std::forward<Item>(needle),
                               std::forward<Compare>(compare));
    if (it == container.cend())
        return {};

    return *it;
}
#endif

// -------------------- is_permutation --------------------
template <typename Container1, typename Container2,
          typename Compare = std::equal_to<ValueType<Container1>>>
#if __cplusplus >= 202002L
requires BinaryPredicateOnContainerValues<Compare, Container1> && BinaryPredicateOnContainerValues<
    Compare, Container2>
#endif
bool is_permutation(const Container1 &container1, const Container2 &container2,
                    Compare &&compare = {})
{
    return std::is_permutation(container1.cbegin(), container1.cend(), container2.cbegin(),
                               container2.cend(), std::forward<Compare>(compare));
}

// -------------------- accumulate --------------------
template <typename Container, typename BinaryOperation,
          typename ReturnType = remove_cvref_t<traits::return_type_of_t<BinaryOperation>>>
#if __cplusplus >= 202002L
requires std::is_invocable_r_v<ReturnType, BinaryOperation, ReturnType, ValueType<Container>>
#endif
    ReturnType accumulate(const Container &container, BinaryOperation &&accumulateFunction,
                          ReturnType initialValue = {})
{
    return std::accumulate(container.cbegin(), container.cend(), initialValue,
                           std::forward<BinaryOperation>(accumulateFunction));
}

// -------------------- get_first_match --------------------
#if __cplusplus >= 201703L
template <typename Container, typename UnaryPredicate>
#if __cplusplus >= 202002L
requires UnaryPredicateOnContainerValues<UnaryPredicate, Container>
#endif
    std::optional<ValueType<Container>> get_first_match(const Container &container,
                                                        UnaryPredicate &&predicate)
{
    auto it =
        std::find_if(container.cbegin(), container.cend(), std::forward<UnaryPredicate>(predicate));
    if (it == container.cend())
        return {};
    else
        return *it;
}
#endif

// -------------------- get_first_match_or_default --------------------
template <typename Container, typename UnaryPredicate>
#if __cplusplus >= 202002L
requires UnaryPredicateOnContainerValues<UnaryPredicate, Container>
#endif
    ValueType<Container> get_first_match_or_default(const Container &container,
                                                    UnaryPredicate &&predicate,
                                                    const ValueType<Container> &defaultValue = {})
{
    auto it =
        std::find_if(container.cbegin(), container.cend(), std::forward<UnaryPredicate>(predicate));
    if (it == container.cend())
        return defaultValue;
    else
        return *it;
}

// -------------------- remove_duplicates --------------------
enum SortOption { do_sort, do_not_sort };
template <typename Container>
void remove_duplicates(Container &container, SortOption sort)
{
    if (sort == do_sort)
        kdalgorithms::sort(container);
    auto it = std::unique(container.begin(), container.end());
    container.erase(it, container.end());
}

// -------------------- has_duplicates --------------------
template <typename Container>
bool has_duplicates(Container &&container, SortOption sort)
{
    auto hasDuplicates = [](const remove_cvref_t<Container> &container) {
        auto pos = std::adjacent_find(container.cbegin(), container.cend());
        return pos != container.cend();
    };

    if (sort == do_not_sort || std::is_sorted(container.cbegin(), container.cend()))
        return hasDuplicates(container);
    else
        return hasDuplicates(sorted(std::forward<Container>(container)));
}

// -------------------- remove / remove_if --------------------
template <typename Container, typename Value>
#if __cplusplus >= 202002L
requires ContainerOfType<Container, Value>
#endif
void remove(Container &container, Value &&value)
{
    auto it = std::remove(container.begin(), container.end(), std::forward<Value>(value));
    container.erase(it, container.end());
}

template <typename Container, typename UnaryPredicate>
#if __cplusplus >= 202002L
requires UnaryPredicateOnContainerValues<UnaryPredicate, Container>
#endif
void remove_if(Container &container, UnaryPredicate &&predicate)
{
    auto it =
        std::remove_if(container.begin(), container.end(), std::forward<UnaryPredicate>(predicate));
    container.erase(it, container.end());
}

} // namespace kdalgorithms
